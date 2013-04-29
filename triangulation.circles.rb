class TopologyGA

  NODES =                   3
  POPULATION =              100
  GENERATIONS =             500
  ACCEPTANCE =              0.05 #metres error

  MAX_DISTANCE =            10.0 #metres
  MIN_DISTANCE =            0.1 #metres
  MAX_SIGNAL_DECAY =        0.2 #%

  SELECTION_SIZE =          5

  CROSSOVER_PROBABILITY =   0.7

  MUTATION_PROBABILITY =    0.1
  MUTATION_AGGRESSIVENESS = 0.1 #%

  FREQUENCY =               2.4 #GHz

  def initialize
    # Generate nodes
    @nodes = (1..NODES).to_a.map {create_node}

    # Init population
    @generation = 0
    @population = (1..POPULATION).to_a.map {create_individual}
    @population = sort_individuals @population

    initial = deep_dup @population.first

    # Start
    best = triangulate

    # Dump
    puts
    puts
    dump_topology
    puts
    puts "INITIALIZATION: #{dump_individual initial}"
    puts "APPROXIMATION: #{dump_individual best}"
  end

  private

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
          i3[:fitness] = get_fitness i3[:data]
          i3[:generation] = @generation
          children.push i3
        end
        @population += children

        # Recalculate generation
        @population = sort_individuals(@population)[0..POPULATION-1]
        best = deep_dup @population.first if @population.first[:fitness] < best[:fitness]

        # Evaluate solution
        break if best[:fitness] <= ACCEPTANCE
      end
      best
    end

    def get_fitness(data)
      error = 0
      data.each_with_index do |coordinate, n|
        distance = Math.sqrt(coordinate[0]**2 + coordinate[1]**2)
        error += (distance - get_distance(@nodes[n][:signal])).abs
      end
      error.round 2
    end

    def get_distance(signal)
      #distance = 10**((db - 20 * Math.log10(FREQUENCY*10e8) + 147.55) / 20)
      distance = Math::const_get(:E) * 1.0/signal # FIXME
    end

    def get_signal(distance)
      #db = 20 * Math.log10(distance) + 20 * Math.log10(FREQUENCY*10e8) - 147.55
      signal = 1.0/Math.log(distance) # FIXME
    end

    def sort_individuals(individual)
      individual.sort_by! {|individual| individual[:fitness]}
    end

    def selection(pool)
      tournament = (1..SELECTION_SIZE).to_a.map {pool[random POPULATION]}
      tournament = sort_individuals tournament
      tournament[0..1]
    end

    def crossover(i1, i2)
      i3 = (random < 0.5) ? deep_dup(i1) : deep_dup(i2)
      return i3 if random < CROSSOVER_PROBABILITY
      NODES.times do |n|
        i3[:data][n] = deep_dup (random < 0.5) ? i1[:data][n] : i2[:data][n]
      end
      i3
    end

    def mutation(i)
      return i if random < MUTATION_PROBABILITY
      node = random NODES
      i[:data][node][0] = (i[:data][node][0] * (1 - MUTATION_AGGRESSIVENESS + random(MUTATION_AGGRESSIVENESS*2))).round 2  # x = x +- 10%
      i[:data][node][1] = (i[:data][node][1] * (1 - MUTATION_AGGRESSIVENESS + random(MUTATION_AGGRESSIVENESS*2))).round 2 # y = y +- 10%
      i
    end

    def create_node
      x, y = rand_coordinate
      decay = random(MAX_SIGNAL_DECAY).round(2)
      distance = Math.sqrt(x**2 + y**2)
      signal = (get_signal(distance)*(1-decay)).round(2)
      {
        x: x,
        y: y,
        signal: signal,
        decay: decay
      }
    end

    def create_individual
      data = (1..NODES).to_a.map {rand_coordinate}
      fitness = get_fitness data
      {
        data: data,
        fitness: fitness,
        generation: @generation,
      }
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

    def deep_dup(hash)
      Marshal.load Marshal.dump hash
    end

    def dump_topology
      @nodes.each_with_index do |node, n|
        puts "NODE #{n}:"
        puts "\tx=#{node[:x]}"
        puts "\ty=#{node[:y]}"
        puts "\ts=#{node[:signal]}"
        puts "\td=#{node[:decay]}"
      end
    end

    def dump_population
      puts "POPULATION:"
      @population.each_with_index do |individual, n|
        puts "\tINDIVIDUAL #{n}: #{dump_individual individual}"
      end
    end

    def dump_individual(individual)
      data = individual[:data].inspect[1..-2].gsub("[", "(").gsub("]", ")")
      fitness = individual[:fitness]
      generation = individual[:generation]
      error = real_error individual[:data]
      "#{data} ~> fitness=#{fitness}, error=#{error}, generation=#{generation}"
    end

    def real_error(data)
      error = 0
      data.each_with_index do |coordinate, n|
        distance = Math.sqrt(coordinate[0]**2 + coordinate[1]**2)
        real_distance = Math.sqrt(@nodes[n][:x]**2 + @nodes[n][:y]**2)
        error += (distance - real_distance).abs
      end
      error.round 2
    end

end

TopologyGA.new