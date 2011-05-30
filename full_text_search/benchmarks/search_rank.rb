require File.expand_path(File.dirname(__FILE__) + "/../benchmarks")

# These take longer, cut down the size
limit = 1000
@r_corpus = @r_corpus[0..limit-1]
@c_corpus = @c_corpus[0..limit-1]

Benchmark.bmbm do |x|
  x.report("ruby search_rank") { RubyFullTextSearchString.new("orange tree").search_rank(@r_corpus) }
  x.report("c search_rank")  { CFullTextSearchString.new("orange tree").search_rank(@c_corpus)  }
end