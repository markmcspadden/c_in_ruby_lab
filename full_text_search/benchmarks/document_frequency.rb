require File.expand_path(File.dirname(__FILE__) + "/../benchmarks")

Benchmark.bmbm do |x|
  x.report("ruby document_frequency") { RubyFullTextSearchString.new("fall").document_frequency(@r_corpus) }
  x.report("c document_frequency")  { CFullTextSearchString.new("fall").document_frequency(@c_corpus)  }
end