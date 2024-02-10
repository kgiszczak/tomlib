# frozen_string_literal: true

require 'bundler/setup'
require 'benchmark/ips'
require 'bigdecimal'

require 'tomlrb'
require 'toml-rb'
require 'perfect_toml'
require 'tomlib'

examples = {
  'small' => File.read('examples/small.toml'), # 100B
  'default' => File.read('examples/default.toml'), # ~5KB
  'big' => File.read('examples/big.toml'), # ~1MB
}

puts "\n=========================== parsing ===========================\n\n"

examples.each do |name, data|
  puts "\n<<<------------------------ #{name} document ------------------------>>>\n\n"

  Benchmark.ips do |x|
    x.report('tomlrb') do
      Tomlrb.parse(data)
    end

    x.report('toml-rb') do
      TomlRB.parse(data)
    end

    x.report('perfect_toml') do
      PerfectTOML.parse(data)
    end

    x.report('tomlib') do
      Tomlib.load(data)
    end

    x.compare!
  end
end

puts "\n\n\n=========================== generating ===========================\n\n"

examples.each do |name, data|
  puts "\n<<<------------------------ #{name} document ------------------------>>>\n\n"

  hash = Tomlib.load(data)

  Benchmark.ips do |x|
    x.report('toml-rb') do
      TomlRB.dump(hash)
    end

    x.report('tomlib') do
      Tomlib.dump(hash, indent: false)
    end

    x.compare!
  end
end
