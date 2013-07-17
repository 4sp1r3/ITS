if ARGV.length != 3
  puts "Usage: routers sets file"
  exit
end

ROUTERS = ARGV[0].to_i
SETS = ARGV[1].to_i
FILE = ARGV[2]

MIN_X, MAX_X = 1, 20
MIN_Y, MAX_Y = 1, 20
MIN_DECAY, MAX_DECAY = 0, 10

def rand(min, max)
  (Random.rand*(MAX_X-MIN_X) + MIN_X).round 2
end

def signal(distance)
  s = Math.log(0.2386 / distance**2) / Math.log(10) * 10
  s += rand(MIN_DECAY, MAX_DECAY)
  s.round 2
end

SETS.times do |n|
  File.open("#{FILE}_#{n+1}.in", "w") do |fp|

    device = {x: rand(MIN_X, MAX_X), y: rand(MIN_Y, MAX_Y)}

    puts "DEVICE: #{device[:x]} #{device[:y]}"
    fp.puts ROUTERS

    ROUTERS.times do |r|
      node = {x: rand(MIN_X, MAX_X), y: rand(MIN_Y, MAX_Y)}
      distance = Math.sqrt((device[:x]-node[:x])**2+(device[:y]-node[:y])**2).round 2
      puts "ROUTER #{r}: #{node[:x]}\t#{node[:y]}\t#{distance}\t#{signal(distance)}"
      fp.puts "#{node[:x]} #{node[:y]} #{signal(distance)}"
    end

    puts

  end
end

Random.rand