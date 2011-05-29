module RubyFullTextSearch
  
  def puts(*args)
    nil
  end
  
  def search_rank(corpus)    
    results = []

    query_words = self.to_words
    corpus_words = corpus.collect{ |c| c.to_words }
    
    query_words.collect do |query_word|
      puts "Query Word: #{query_word}"

      qf = query_word.word_frequency(query_words)
      puts "Query Frequency: #{qf}"
      
      puts corpus_words.collect{ |w| w.join(" ") }
      
      corpus_words.each do |words|
        r = 0.0
        
        puts "Corpus Words: #{words}"
        words.each do |word|
          puts "Corpus Word: #{word}"
          
          if query_word == word # No stemming, no regexing, just straight up matching
            puts "Match found on #{word} in #{corpus_words}"
                    
            tf = word.word_frequency(words)
            puts "Term Frequency: #{tf}"
          
            df = word.document_frequency(corpus)
            puts "Document Frequency: #{df}"
          
            w = tf * (1/df)
            puts "Weight: #{w}"
          
            r += qf*w
            puts "R: #{r}"
          end
        end
        
        # Initialize or Combine results
        if r > 0
          if previous = results.detect{ |result| result[1] == words.join(" ") }
            previous[0] += r
          else
            results << [r, words.join(" ")]
          end
        end
      end
    end
    
    results.sort.reverse
  end
  
  def word_frequency(words)
    times = words.select{ |w| w == self }.count.to_f # There's gotta be a better way...      
    times/words.size.to_f
  end
  
  def document_frequency(documents)
    times = documents.select{ |d| d.to_words.include?(self) }.count.to_f
    times/documents.size.to_f
  end
  
  def to_words
    self.split(" ")#.collect{ |w| w.gsub(/[[:punct:]]/,"").downcase }
  end
  
end