# frozen_string_literal: true

require 'bundler/gem_tasks'
require 'rubocop/rake_task'
require 'rake/extensiontask'

RuboCop::RakeTask.new

Rake::ExtensionTask.new('tomlib') do |ext|
  ext.lib_dir = 'lib/tomlib'
end

task build: :compile
task default: %i[clobber compile rubocop]
