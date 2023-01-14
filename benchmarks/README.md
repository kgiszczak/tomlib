# Benchmarks

This is a comparison of this gem with [Tomlrb](https://github.com/fbernier/tomlrb)
and [toml-rb](https://github.com/emancu/toml-rb).

It measures performance using three files:

* `examples/small.toml` (100B)
* `examples/default.toml` (~5KB)
* `examples/big.toml` (~1MB)

## Usage

Install all the dependencies:

    $ bundle install

and run benchmarks:

    $ ruby benchmarks.rb

## Results

Ruby version: ruby 3.2.0 (2022-12-25 revision a528908271) [arm64-darwin22]

### Parsing (i/s)

|gem         |small.toml             |default.toml           |big.toml|
|------------|-----------------------|-----------------------|--------|
|Tomlib      |536.316k               |21.701k                |26.868
|perfect_toml|105.363k (5.09x slower)|4.499k (4.82x)         |16.050 (1.67x slower)
|Tomlrb      |21.997k (24.38x slower)|915.702 (23.70x slower)|2.741 (9.80x slower)
|toml-rb     |1.232k (435.46x slower)|32.186 (674.24x slower)|0.152 (176.45x slower)

### Generating (i/s)

Note! Tomlrb doesn't support generating TOML documents and perfect_toml crashes under Ruby 3.

|gem    |small.toml             |default.toml         |big.toml|
|-------|-----------------------|---------------------|--------|
|Tomlib |252.027k               |12.469k              |51.616
|toml-rb|159.683k (1.58x slower)|6.965k (1.79x slower)|0.580 (89.35x slower)

---

With YJIT enabled: ruby 3.2.0 (2022-12-25 revision a528908271) +YJIT [arm64-darwin22]

### Parsing (i/s)

|gem         |small.toml             |default.toml           |big.toml|
|------------|-----------------------|-----------------------|--------|
|Tomlib      |547.264k               |22.098k                |26.537
|perfect_toml|142.496k (3.84x slower)|6.218k (3.55x)         |22.710 (1.17x slower)
|Tomlrb      |30.115k (18.17x slower)|1.292k (17.10x slower) |3.900 (6.80x slower)
|toml-rb     |1.858k (294.62x slower)|55.148 (400.69x slower)|0.220 (120.64x slower)

### Generating (i/s)

|gem    |small.toml             |default.toml         |big.toml|
|-------|-----------------------|---------------------|--------|
|Tomlib |428.621k               |20.443k              |89.778
|toml-rb|230.362k (1.86x slower)|9.020k (2.27x slower)|0.551 (162.80x slower)
