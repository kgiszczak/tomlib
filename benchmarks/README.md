# Benchmarks

Comparison of this gem with [Tomlrb](https://github.com/fbernier/tomlrb)
and [toml-rb](https://github.com/emancu/toml-rb).

It beanchmarks parsing and generating three files:

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
|Tomlib|176.838k|6.577k|11.392|
|Tomlrb|10.697k (16.53x slower)|416.441 (15.79x slower)|1.211 (9.40x slower)
|toml-rb|810.809 (218.10x slower)|20.683 (318.01x slower)|0.080 (142.09x slower)

### Generating (i/s)

Note - Tomlrb gem doesn't support generating TOML documents.

|gem|small.toml|default.toml|big.toml|
|---|----------|------------|--------|
|Tomlib|137.698k|4.741k|22.785|
|toml-rb|64.312k (2.14x slower)|2.672k (1.77x slower)|0.129 (175.98x slower)
