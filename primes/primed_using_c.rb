require 'primed'

class Integer
  include Primed
end

numbers = (2..2000000).to_a
 
numbers = numbers.select { |n| n.prime? }
puts numbers.inject { |result, element| result = element + result }