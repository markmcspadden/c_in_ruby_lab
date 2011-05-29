require 'test/unit'

require 'full_text_search'

class FullTextSearch < Test::Unit::TestCase
  def setup
    @corpus = ["The apple doesn't fall far from the tree.",
              "Johnny Appleseed planted many an apple trees and had an apple a day.",
              "I would like an orange tree."]
              
    @r_corpus = @corpus.collect{ |c| RubyFullTextSearchString.new(c) }
    @c_corpus = @corpus.collect{ |c| CFullTextSearchString.new(c) }
              
    @s1_expected = [[0.46, "Johnny Appleseed planted many an apple trees and had an apple a day."],
                [0.1875, "The apple doesn't fall far from the tree."]]    
                
    @s2_expected = [[0.5, "I would like an orange tree."]] 
    
    @s3_expected = [[0.375, "I would like an orange tree."],
                    [0.09375, "The apple doesn't fall far from the tree."]]        
  end  
  
  def test_ruby_to_words
    assert_equal ["this", "is", "an", "apple."], RubyFullTextSearchString.new("This is an apple.".downcase).to_words
  end
  
  def test_ruby_single_word_query    
    result = RubyFullTextSearchString.new("apple").search_rank(@r_corpus)
    result.first[0] = (result.first.first*100).round/100.0 # Silly
    
    assert_equal @s1_expected, result
  end
  def test_ruby_single_word_query_again
    result = RubyFullTextSearchString.new("orange").search_rank(@r_corpus)
    assert_equal @s2_expected, result
  end
  def test_ruby_multiple_word_query                
    result = RubyFullTextSearchString.new("orange tree.").search_rank(@r_corpus)
    assert_equal @s3_expected, result
  end
  
  def test_c_to_words
    assert_equal ["this", "is", "an", "apple."], CFullTextSearchString.new("This is an apple.".downcase).to_words
  end
  
  def test_c_single_word_query    
    result = CFullTextSearchString.new("apple").search_rank(@c_corpus)
    result.first[0] = (result.first.first*100).round/100.0 # Silly
    
    assert_equal @s1_expected, result
  end
  def test_c_single_word_query_again
    result = CFullTextSearchString.new("orange").search_rank(@c_corpus)
    assert_equal @s2_expected, result
  end
  def test_c_multiple_word_query                
    result = CFullTextSearchString.new("orange tree.").search_rank(@c_corpus)
    assert_equal @s3_expected, result
  end
  
end