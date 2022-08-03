# frozen_string_literal: true

require 'date'

require_relative 'tomlib/dumper'
require_relative 'tomlib/tomlib'
require_relative 'tomlib/version'

# Main library namespace
#
# @example parsing TOML data into Ruby Hash
#
#   puts Tomlib.load(<<~TOML)
#     firstName = "John"
#     lastName = "Doe"
#   TOML
#
#   # => { 'firstName' => 'John', 'lastName' => 'Doe' }
#
# @example generating TOML from Ruby Hash
#
#   puts Tomlib.dump({ 'firstName' => 'John', 'lastName' => 'Doe' })
#
#   # =>
#   firstName = "John"
#   lastName = "Doe"
#
# @api public
module Tomlib
  # Dump Ruby Hash into TOML format
  #
  # @param [Hash] hash
  # @param [true, false] indent (default: true)
  #
  # @return [String]
  #
  # @example
  #   puts Tomlib.dump({ 'firstName' => 'John', 'lastName' => 'Doe' })
  #   # =>
  #   firstName = "John"
  #   lastName = "Doe"
  #
  # @api public
  def self.dump(hash, indent: true)
    Dumper.new.dump(hash, use_indent: indent)
  end
end
