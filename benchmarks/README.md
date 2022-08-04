# Benchmarks

Compare this gem with [Tomlrb](https://github.com/fbernier/tomlrb)
and [toml-rb](https://github.com/emancu/toml-rb).

It measures parsing and generating performance using three files:

* `examples/small.toml` (100B)
* `examples/default.toml` (~5KB)
* `examples/big.toml` (~1MB)

## Usage

Install all the dependencies:

    $ bundle install

and run benchmarks:

    $ ruby benchmarks.rb

## Results

### Parsing (i/s)

|gem|small.toml|default.toml|big.toml|
|---|----------|------------|--------|
|Tomlib|184.579k|6.484k|11.453|
|perfect_toml|56.266k (3.28x slower)|2.155k (3.01x)|7.694 (1.49x slower)
|Tomlrb|10.366k (17.81x slower)|374.509 (17.31x slower)|1.148 (9.98x slower)
|toml-rb|811.421 (227.48x slower)|20.135 (322.05x slower)|0.077 (148.73x slower)

### Generating (i/s)

Note - Tomlrb gem doesn't support generating TOML documents
and perfect_toml doesn't work under Ruby 3.

|gem|small.toml|default.toml|big.toml|
|---|----------|------------|--------|
|Tomlib|133.456k|5.615k|23.105|
|toml-rb|65.968k (2.02x slower)|2.695k (2.08x slower)|0.146 (158.59x slower)
