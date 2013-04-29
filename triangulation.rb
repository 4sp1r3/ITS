require "gnuplot"

class TopologyGA

  NODES =                   10
  FREQUENCY =               2.4   #GHz

  POPULATION =              10
  GENERATIONS =             100

  MAX_DISTANCE =            5.0   #metres
  MIN_DISTANCE =            0.5   #metres
  MAX_SIGNAL_DECAY =        0.0   #%
  ACCEPTANCE =              1     #metres error

  SELECTION_SIZE =          5

  CROSSOVER_PROBABILITY =   0.7

  MUTATION_PROBABILITY =    0.2
  MAX_MUTATION_XY =         1     #metres
  MAX_MUTATION_DECAY =      0.1   #%

  MAX_INIT_DECAYS =         0   #%
  MIN_INIT_DECAYS =         0   #%

  def initialize
    # Plot
    @plot = {
      nodes: [],
      individuals: [],
      real: [],
      initial: [],
      ancestors: [],
      best: []
    }

    # Generate nodes
    @nodes = Array.new(NODES).map {create_node}
    @nodes.each {|node| @plot[:nodes].push [node[:x], node[:y]]}
    @plot[:real] = [[0, 0]]

    # Initialize population
    @generation = 0
    @population = Array.new(POPULATION).map {create_individual}
    @population = unique sort @population
    @population.each {|individual| @plot[:ancestors].push [individual[:x], individual[:y]]}

    initial = deep_dup @population.first
    @population.each {|individual| @plot[:individuals].push [individual[:x], individual[:y]]}
    @plot[:initial] = [[initial[:x], initial[:y]]]

    #dump_population # FIXME

    # Start algorithm
    best = triangulate
    @plot[:best] = [[best[:x], best[:y]]]

    # Print results
    puts
    puts
    dump_topology
    puts
    puts "INIT: #{dump_individual initial}"
    puts "BEST: #{dump_individual best}"
    plot
  end

  private

    # ALGORITHM

    def triangulate
      best = deep_dup @population.first

      GENERATIONS.times do
        @generation += 1
        print "\rGENERATION: #{@generation}"

        children = []
        POPULATION.times do
          # Genetic algorithm
          i1, i2 = selection @population
          i3 = crossover i1, i2
          i3 = mutation i3

          # Update population
          i3[:fitness] = fitness i3[:x], i3[:y], i3[:decays]
          i3[:generation] = @generation
          children.push i3
          @plot[:individuals].push [i3[:x], i3[:y]]
        end
        # Recalculate generation
        @population += children
        @population = unique sort(@population)[0..POPULATION]
        best = deep_dup @population.first if @population.first[:fitness] < best[:fitness]

        # Evaluate solution
        break if best[:fitness] <= ACCEPTANCE
      end

      best
    end

    def fitness(x, y, decays)
      error = 0
      @nodes.each_with_index do |node, n|
        distance = Math.sqrt((node[:x]-x)**2 + (node[:y]-y)**2)
        intensity = node[:intensity] * (1 + decays[n])
        error += (distance - get_distance(intensity)).abs
      end
      error.round 2
    end

    def selection(individuals)
      tournament = sort Array.new(SELECTION_SIZE).map {individuals[random [SELECTION_SIZE, individuals.length].min]}
      tournament[0..1]
    end

    def crossover(i1, i2)
      i3 = deep_dup i1
      if random < CROSSOVER_PROBABILITY
        i3[:x] = (i1[:x] + i2[:x]) / 2
        i3[:y] = (i1[:y] + i2[:y]) / 2
        NODES.times do |n|
          i3[:decays][n] += (i1[:decays][n] + i2[:decays][n]) / 2
        end
      end
      i3
    end

    def mutation(i)
      return i if random < MUTATION_PROBABILITY
      i[:x] = (i[:x] + random(MAX_MUTATION_XY*2) - MAX_MUTATION_XY).round 2  # x = x +- MAX_MUTATION_XY
      i[:y] = (i[:y] + random(MAX_MUTATION_XY*2) - MAX_MUTATION_XY).round 2  # y = y +- MAX_MUTATION_XY
      NODES.times do |n|
        i[:decays][n] = (i[:decays][n] + random(MAX_MUTATION_DECAY*2) - MAX_MUTATION_DECAY).round # decay = decay +- MAX_MUTATION_DECAY
        i[:decays][n] = 0 if i[:decays][n] < 0
        i[:decays][n] = 1 if i[:decays][n] > 1
      end
      i
    end

    # INITIALIZE

    def create_node
      x, y = rand_coordinate
      distance = Math.sqrt(x**2 + y**2).round 2
      signal = get_signal(distance).round 2
      decay = random(MAX_SIGNAL_DECAY).round 2
      intensity = (signal*(1-decay)).round 2
      {
        x: x,
        y: y,
        distance:   distance,
        signal:     signal,
        decay:      decay,
        intensity:  intensity
      }
    end

    def create_individual
      x, y = rand_coordinate
      decays = Array.new(NODES).map {random(MIN_INIT_DECAYS, MAX_INIT_DECAYS).round 2}
      {
        x:          y,
        y:          x,
        decays:     decays,
        fitness:    fitness(x, y, decays),
        generation: @generation
      }
    end

    # UTILS

    def get_distance(signal)
      #distance = 10**((db - 20 * Math.log10(FREQUENCY*10e8) + 147.55) / 20)
      #distance = Math::const_get(:E) ** (1.0/signal) # FIXME
      distance = (Math.sqrt(1.0 / signal) - 1) / 0.03
    end

    def get_signal(distance)
      #db = 20 * Math.log10(distance) + 20 * Math.log10(FREQUENCY*10e8) - 147.55
      #signal = 1.0/Math.log(distance) # FIXME
      signal = 1.0/(distance*0.03+1)**2
    end

    def sort(individuals)
      individuals.sort_by! {|individual| individual[:fitness]}
    end

    def unique(individuals)
      coordinates = {}
      uniques = []
      individuals.each do |individual|
        unless coordinates[individual[:x]] and coordinates[individual[:x]][individual[:y]] and coordinates[individual[:x]][individual[:y]][individual[:decays]]
          coordinates[individual[:x]] = {} unless coordinates[individual[:x]]
          coordinates[individual[:x]][individual[:y]] = {} unless coordinates[individual[:x]][individual[:y]]
          coordinates[individual[:x]][individual[:y]][individual[:decays]] = true
          uniques.push individual
        end
      end
      uniques
    end

    def rand_coordinate
      x = (-1)**(random 2) * random(MIN_DISTANCE, MAX_DISTANCE).round(2)
      y = (-1)**(random 2) * random(MIN_DISTANCE, MAX_DISTANCE).round(2)
      [x, y]
    end

    def random(m=nil, n=nil)
      max = n || m || 1.0
      min = (n != nil) ? m : 0.0
      r = (min != max) ? min + Random.rand(max-min) : 0
      return (m.is_a? Float or n.is_a? Float or m.is_a? NilClass) ? r.to_f : r.to_i
    end

    # DUMP

    def deep_dup(hash)
      Marshal.load Marshal.dump hash
    end

    def dump_topology
      @nodes.each_with_index do |node, n|
        puts "NODE #{n}:"
        puts "\tx=#{node[:x]}"
        puts "\ty=#{node[:y]}"
        puts "\tdistance=#{node[:distance]}"
        puts "\tsignal=#{node[:signal]}"
        puts "\tdecay=#{node[:decay]}"
        puts "\tintensity=#{node[:intensity]}"
      end
    end

    def dump_population
      puts "POPULATION:"
      @population.each_with_index do |individual, n|
        puts "\tINDIVIDUAL #{n}: #{dump_individual individual}"
      end
    end

    def dump_individual(individual)
      "(#{individual[:x]}, #{individual[:y]}) #{individual[:decays].inspect} ~> fitness=#{individual[:fitness]}, generation=#{individual[:generation]}"
    end

    def plot
      Gnuplot.open do |gp|
        Gnuplot::Plot.new(gp) do |plot|
          limit = MAX_DISTANCE*1.3
          plot.xrange "[#{-limit}:#{limit}]"
          plot.yrange "[#{-limit}:#{limit}]"

          plot.data << Gnuplot::DataSet.new(@plot[:individuals].transpose) do |ds|
            ds.with = "points pt 7 ps 0.5 lc rgb '#DDDDDD'"
            ds.title = "Individuals"
          end

          plot.data << Gnuplot::DataSet.new(@plot[:ancestors].transpose) do |ds|
            ds.with = "points pt 7 ps 0.5 lc rgb '#888888'"
            ds.title = "Ancestors"
          end

          plot.data << Gnuplot::DataSet.new(@plot[:best].transpose) do |ds|
            ds.with = "points pt 7 ps 1.5 lc rgb '#7680FF'"
            ds.title = "Best"
          end

          plot.data << Gnuplot::DataSet.new(@plot[:real].transpose) do |ds|
            ds.with = "points pt 7 ps 1.25 lc rgb '#55FF55'"
            ds.title = "Real"
          end

          plot.data << Gnuplot::DataSet.new(@plot[:nodes].transpose) do |ds|
            ds.with = "points pt 7 ps 1 lc rgb '#FF0000'"
            ds.title = "Nodes"
          end

          plot.data << Gnuplot::DataSet.new(@plot[:initial].transpose) do |ds|
            ds.with = "points pt 7 ps 0.7 lc rgb '#000000'"
            ds.title = "Initial"
          end
        end
      end
    end

end

TopologyGA.new