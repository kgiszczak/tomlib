# frozen_string_literal: true

require_relative 'lib/tomlib/version'

Gem::Specification.new do |spec|
  spec.name = 'tomlib'
  spec.version = Tomlib::VERSION
  spec.authors = ['Kamil Giszczak']
  spec.email = ['beerkg@gmail.com']

  spec.summary = 'Fast TOML parser and generator with native extension.'
  spec.description = 'Fast TOML parser and generator with native extension.'
  spec.homepage = 'https://github.com/kgiszczak/tomlib'
  spec.license = 'MIT'

  spec.metadata['allowed_push_host'] = 'https://rubygems.org'

  spec.metadata['homepage_uri'] = 'https://github.com/kgiszczak/tomlib'
  spec.metadata['source_code_uri'] = 'https://github.com/kgiszczak/tomlib'
  spec.metadata['changelog_uri'] = 'https://github.com/kgiszczak/tomlib/blob/master/CHANGELOG.md'
  spec.metadata['bug_tracker_uri'] = 'https://github.com/kgiszczak/tomlib/issues'

  spec.files = Dir['CHANGELOG.md', 'LICENSE.txt', 'README.md', 'shale.gemspec', 'lib/**/*']
  spec.require_paths = ['lib']

  spec.extensions = ['ext/tomlib/extconf.rb']

  spec.required_ruby_version = '>= 2.7.0'
end
