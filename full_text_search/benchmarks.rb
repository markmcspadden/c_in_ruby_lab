require 'benchmark'

require File.expand_path(File.dirname(__FILE__) + '/full_text_search')

@corpus = ["The apple doesn't fall far from the tree.",
          "Johnny Appleseed planted many an apple trees and had an apple a day.",
          "I would like an orange tree."]
          
100000.times do
  @corpus << @corpus[rand(@corpus.size)]
end          
          
@r_corpus = @corpus.collect{ |c| RubyFullTextSearchString.new(c) }
@c_corpus = @corpus.collect{ |c| CFullTextSearchString.new(c) }