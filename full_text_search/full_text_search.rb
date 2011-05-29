# Require both
require 'ruby_full_text_search'
require 'c_full_text_search'

class RubyFullTextSearchString < String
  include RubyFullTextSearch
end

class CFullTextSearchString < String
  include RubyFullTextSearch
  include CFullTextSearch
end