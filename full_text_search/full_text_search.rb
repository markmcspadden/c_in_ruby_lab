# Require both
require File.expand_path(File.dirname(__FILE__) + '/ruby_full_text_search')
require File.expand_path(File.dirname(__FILE__) + '/c_full_text_search')

class RubyFullTextSearchString < String
  include RubyFullTextSearch
end

class CFullTextSearchString < String
  include RubyFullTextSearch
  include CFullTextSearch
end