Dir.glob(File.dirname(__FILE__) + "/*.rb").each do |f|
  unless f["all.rb"]
    puts "\n\nPerforming Benchmark from #{f}"
    require f
  end
end