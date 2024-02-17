## [0.7.2] - [unreleased]

- Remove "double_heap" deprecation warning

## [0.7.1] - 2024-02-17

- Remove "missing bigdecimal dependency" warning

## [0.7.0] - 2024-02-10

- Update tomlc99 to the latest version
- Parse very large numbers as Infinity
- Add support for Ruby 3.3
- Drop support for Ruby 2.7 and 2.7

## [0.6.0] - 2023-05-05

- Correctly escape special characters

## [0.5.0] - 2022-08-16

- Add support for Ruby 2.6

## [0.4.0] - 2022-08-06

- Correctly dump empty arrays

## [0.3.0] - 2022-08-05

- Add ext/* to bundled files

## [0.2.0] - 2022-08-04

- Refactor Tomlib::Dumper to be a littel faster and generate squashed nested tables
  ```
  e.g. instead of this:
  [a]
  [a.b]
  [a.b.c]

  the output will be this:
  [a.b.c]
  ```
- Add mention about compliance and passed tests in README.
- Declare global variables with `rb_global_variable`.
It may prevent VM from crashing in some cases.

## [0.1.0] - 2022-08-02

- Initial release
