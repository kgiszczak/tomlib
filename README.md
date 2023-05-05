# Tomlib

Tomlib is a TOML parser and generator for Ruby. It uses native C extension based on
fast and standards-compliant [tomlc99](https://github.com/cktan/tomlc99) parser.

## Compliance

Tomlib is TOML v1.0 compliant.
It passes both [BurntSushi/toml-test](https://github.com/BurntSushi/toml-test) and
[iarna/toml-spec-tests](https://github.com/iarna/toml-spec-tests).

## Installation

Tomlib supports Ruby (MRI) 2.6+

Add this line to your application's Gemfile:

```ruby
gem 'tomlib'
```

And then execute:

```
$ bundle install
```

Or install it yourself as:

```
$ gem install tomlib
```

## Usage

To parse a TOML document use:

```ruby
require 'tomlib'

Tomlib.load(<<~TOML)
firstName = "John"
lastName = "Doe"
hobbies = [ "Singing", "Dancing" ]

[address]
city = "London"
zip = "E1 6AN"

[address.street]
name = "Oxford Street"
TOML

# =>
#
# {
#   "firstName" => "John",
#   "lastName" => "Doe",
#   "hobbies" => ["Singing", "Dancing"],
#   "address" => {
#     "city"=>"London",
#     "zip"=>"E1 6AN",
#     "street"=>{ "name"=>"Oxford Street" }
#   }
# }
```

To generate a TOML document from Ruby Hash use:

```ruby
require 'tomlib'

Tomlib.dump({
  "firstName" => "John",
  "lastName" => "Doe",
  "hobbies" => ["Singing", "Dancing"],
  "address" => {
    "city"=>"London",
    "zip"=>"E1 6AN",
    "street"=>{ "name"=>"Oxford Street" }
  }
})

# =>
#
# firstName = "John"
# lastName = "Doe"
# hobbies = [ "Singing", "Dancing" ]
#
# [address]
# city = "London"
# zip = "E1 6AN"
#
#   [address.street]
#   name = "Oxford Street"
```

If you don't need indentation use:

```ruby
require 'tomlib'

Tomlib.dump(hash, indent: false)

# =>
#
# firstName = "John"
# lastName = "Doe"
# hobbies = [ "Singing", "Dancing" ]
#
# [address]
# city = "London"
# zip = "E1 6AN"
#
# [address.street]
# name = "Oxford Street"
```

## Performance

When parsing documents, `Tomlib` is more than 600x (400x with yjit) faster than `toml-rb`,
23x (17x with yjit) faster than `Tomlrb` and almost 5x (3.5x with yjit)
faster than `perfect_toml` (~5KB TOML document size).

When generating TOML documents, it is about 1.5x (1.7x with yjit) faster than `toml-rb`.

For full comparison take a look at
[benchmarks](https://github.com/kgiszczak/tomlib/tree/master/benchmarks)

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/kgiszczak/tomlib.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
