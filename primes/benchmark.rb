require 'benchmark'

Benchmark.bmbm do |x|
  x.report("ruby primed") { require 'primed_using_ruby' }
  x.report("c primed")  { require 'primed_using_c'  }
end