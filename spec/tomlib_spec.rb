# frozen_string_literal: true

require 'json'
require 'time'
require 'tomlib'
require 'yaml'

def cast_float(value)
  case value
  when 'inf', '+inf'
    Float::INFINITY
  when '-inf'
    -Float::INFINITY
  when 'nan', '+nan', '-nan'
    Float::NAN
  else
    value.to_f
  end
end

def cast_value(value)
  case value['type']
  when 'integer'
    value['value'].to_i
  when 'float'
    cast_float(value['value'])
  when 'bool'
    value['value'] == 'true'
  when 'datetime', 'datetime-local'
    Time.parse(value['value'])
  when 'date-local', 'date'
    Date.parse(value['value'])
  else
    value['value']
  end
end

def test_case_to_hash(data)
  if data.is_a?(Array)
    data.map { |v| test_case_to_hash(v) }
  elsif data.key?('type') && data.key?('value')
    cast_value(data)
  else
    data.to_h { |k, v| [k, test_case_to_hash(v)] }
  end
end

RSpec.describe Tomlib do
  describe '.load' do
    context 'valid' do
      tests = Dir[File.expand_path('examples/parser/valid/**/*.toml', File.dirname(__FILE__))]

      tests.each do |toml|
        it toml do
          yaml = toml.gsub('.toml', '.yaml')
          json = toml.gsub('.toml', '.json')

          if File.exist?(yaml)
            expected = YAML.safe_load(File.read(yaml), permitted_classes: [Date, Time])
          else
            expected = test_case_to_hash(JSON.parse(File.read(json)))
          end

          result = described_class.load(File.read(toml))

          expect(result).to eq(expected)
        end
      end

      it 'handles NaN' do
        result = described_class.load(<<~TOML)
          sf4 = nan
          sf5 = +nan
          sf6 = -nan
        TOML

        expect(result['sf4'].nan?).to eq(true)
        expect(result['sf5'].nan?).to eq(true)
        expect(result['sf6'].nan?).to eq(true)
      end
    end

    context 'errors' do
      tests = Dir[File.expand_path('examples/parser/invalid/**/*.toml', File.dirname(__FILE__))]

      tests.each do |toml|
        it toml do
          expect do
            described_class.load(File.read(toml))
          end.to raise_error(Tomlib::ParseError)
        end
      end
    end
  end
end
