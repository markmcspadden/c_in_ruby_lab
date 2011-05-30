require File.expand_path(File.dirname(__FILE__) + "/../benchmarks")

Benchmark.bmbm do |x|
  x.report("ruby to_words") { @r_corpus.each{ |r| r.to_words } }
  x.report("c to_words")  { @c_corpus.each { |c| c.to_words }  }
end