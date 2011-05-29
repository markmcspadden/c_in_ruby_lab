require 'benchmark'

require 'full_text_search'

@corpus = ["The apple doesn't fall far from the tree.",
          "Johnny Appleseed planted many an apple trees and had an apple a day.",
          "I would like an orange tree."]
          
1000.times do
  @corpus << @corpus[rand(@corpus.size)]
end          
          
@r_corpus = @corpus.collect{ |c| RubyFullTextSearchString.new(c) }
@c_corpus = @corpus.collect{ |c| CFullTextSearchString.new(c) }

Benchmark.bmbm do |x|
  x.report("ruby to_words") { RubyFullTextSearchString.new("orange tree").search_rank(@r_corpus) }
  x.report("c to_words")  { CFullTextSearchString.new("orange tree").search_rank(@c_corpus)  }
end