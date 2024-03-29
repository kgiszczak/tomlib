# frozen_string_literal: true

require 'simplecov'

SimpleCov.start do
  add_filter '/spec/'
end

RSpec.configure do |config|
  config.expect_with :rspec do |expectations|
    expectations.include_chain_clauses_in_custom_matcher_descriptions = true
  end

  config.mock_with :rspec do |mocks|
    mocks.verify_partial_doubles = true
  end

  config.shared_context_metadata_behavior = :apply_to_host_groups

  config.warnings = true
  config.order = :random
end

require 'tomlib'

if GC.respond_to?(:verify_compaction_references)
  # This method was added in Ruby 3.0.0. Calling it this way asks the GC to
  # move objects around, helping to find object movement bugs.
  begin
    begin
      GC.verify_compaction_references(expand_heap: true, toward: :empty)
    rescue ArgumentError
      GC.verify_compaction_references(double_heap: true, toward: :empty)
    end
  rescue NotImplementedError
    # Some platforms don't support compaction
  end
end
