## [0.4.0] - [2022-08-06]

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
