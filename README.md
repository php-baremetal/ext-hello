# ext-hello

The minimal example extension of php-baremetal. It adds one function, `bm_hello()`, to the PHP that runs on your
board, and nothing else: no hardware, no HAL, no options. Require it to check that a project builds the packages
it asks for, or read it as the smallest possible `bm-ext` package: one C file and a `composer.json`.

ext-hello is pure: it has no HAL, so it works on every platform.

## Install

In a project created with `phpbm init`:

```bash
composer require php-baremetal/ext-hello
```

## Example

```php
<?php
echo bm_hello(), "\n";   // hello from ext-hello package
```

## Documentation

- [Overview](docs/overview.md): what it is, install, the package layout to copy.
- [PHP API](docs/usage/php-api.md): `bm_hello()`.
- [Check that a package is built in](docs/recipes/check-the-build.md): a first project, end to end.

## License

MIT.
