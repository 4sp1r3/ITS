if ARGV.length != 3
  puts "Usage: routers sets file"
  exit
end

ROUTERS = ARGV[0].to_i
SETS = ARGV[1].to_i
FILE = ARGV[2]

MIN_X, MAX_X = 1, 7.5
MIN_Y, MAX_Y = 1, 7.5
MIN_DECAY, MAX_DECAY = 0, 2

def rand(min, max, sign)
  value = (Random.rand*(max-min) + min).round 2
  value *= (Random.rand < 0.5) ? 1 : -1 if sign
  value
end

def signal(distance)
  s = Math.log(0.2386 / distance**2) / Math.log(10) * 10
  s.round 2
end

SETS.times do |n|
  fp_in = File.open("#{FILE}_#{n+1}.in", "w")
  fp_ck = File.open("#{FILE}_#{n+1}.ck", "w")

  device = {x: rand(MIN_X, MAX_X, true), y: rand(MIN_Y, MAX_Y, true)}

  check = "DEVICE:\t\tx=#{device[:x]}\t\ty=#{device[:y]}"
  puts check
  fp_ck.puts check
  fp_in.puts ROUTERS

  ROUTERS.times do |r|
    node = {x: rand(MIN_X, MAX_X, true), y: rand(MIN_Y, MAX_Y, true)}
    distance = Math.sqrt((device[:x]-node[:x])**2+(device[:y]-node[:y])**2).round 2
    decay = rand(MIN_DECAY, MAX_DECAY, false)
    signal = signal(distance)

    check = "ROUTER #{r}:\tx=#{node[:x]}\t\ty=#{node[:y]}\t\td=#{distance}\t\ts=#{signal}\t\ta=#{decay}"
    puts check
    fp_ck.puts check
    fp_in.puts "#{node[:x]} #{node[:y]} #{signal-decay}"
  end

  puts
  fp_in.close
  fp_ck.close
end

Random.rand