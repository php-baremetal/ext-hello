---
eyebrow: 'Package · Extension'
lede:    'The minimal example extension: it adds bm_hello() to the PHP that runs on the board and nothing else. Use it to check that a project builds its packages in; it needs no other package, on any platform.'
see_also:
  - { href: './usage/php-api.md', meta: 'PHP API' }
  - { href: './recipes/check-the-build.md', meta: 'Recipe' }
  - { href: 'package:php-baremetal/ext-mem#docs/overview.md', meta: 'Extension', label: 'ext-mem' }
prev: { label: 'No previous page', href: '#' }
next: { label: 'PHP API', href: './usage/php-api.md' }
---

# Hello extension

ext-hello adds one function, `bm_hello()`, to the PHP that runs on your board. It does nothing useful on purpose.
It serves two purposes:

- **Checking a project.** If `bm_hello()` works, the project picks up the packages it requires, builds them in and
  runs your script.
- **Showing the smallest extension package.** One C file and a `composer.json`; see the layout below.

Require it while setting up a new project, or when a package you required does not show up and you want to tell a
project problem from a package problem. Remove it once the project works.

## Requirements

Pure. It touches no hardware and requires no HAL, so conductor adds nothing for it and it builds for whatever
platform your project targets. The only requirement is `php >=8.3`. The extension's PHP module is `hello`.

## Install

<!-- @steps -->
- **Install conductor once per machine**

  `composer global require php-baremetal/conductor` keeps the plugin active during the first solve of a new
  project.

- **Create the project**

  `phpbm init my-hello` writes `composer.json` with conductor (`^1.0`, allowed as a plugin), the package
  registry, and the SDK, board, runtime and storage you pick.

- **Require the extension**

  `composer require php-baremetal/ext-hello`

- **Build and flash**

  `phpbm flash` builds the firmware and flashes it; `phpbm monitor` opens the serial console. The function exists
  only in a firmware built with the package.
<!-- @endsteps -->

The resulting `composer.json`, for a Waveshare ESP32-S3-Touch-LCD-1.85B:

<!-- @code-block language="json" label="composer.json" -->
```json
{
  "name": "acme/my-hello",
  "type": "project",
  "repositories": [
    { "type": "composer", "url": "https://repository.php-baremetal.com", "canonical": true }
  ],
  "require": {
    "php-baremetal/conductor": "^1.0",
    "php-baremetal/ext-hello": "^1.0"
  },
  "config": {
    "allow-plugins": { "php-baremetal/conductor": true },
    "platform": { "php": "8.5.11" }
  },
  "extra": {
    "baremetal": {
      "sdk": "esp32@^1.0",
      "board": "waveshare-esp32-s3-touch-lcd-1.85b",
      "runtime": "init-loop",
      "storage": "embedded"
    }
  }
}
```
<!-- @endcode-block -->

## PHP API

| Function | Returns | Meaning |
| --- | --- | --- |
| `bm_hello()` | `string` | The fixed greeting `"hello from ext-hello package"`. |

<!-- @code-block language="php" label="project-src/index.php" -->
```php
<?php
echo bm_hello(), "\n";      // hello from ext-hello package
```
<!-- @endcode-block -->

Full reference: [PHP API](./usage/php-api.md).

## The package, as a template

An extension package is a Composer package of type `bm-ext` with C sources. ext-hello is the whole of it:

<!-- @code-block language="json" label="composer.json" -->
```json
{
    "name": "php-baremetal/ext-hello",
    "type": "bm-ext",
    "require": { "php": ">=8.3" },
    "extra": {
        "baremetal": { "module": "hello" }
    }
}
```
<!-- @endcode-block -->

`extra.baremetal.module` is the module name; the C file in `src/` defines the matching `zend_module_entry` and its
functions. A package that needs hardware adds `php-baremetal/<x>-hal` to `require` and calls the HAL header from
its C code; [ext-mem](package:php-baremetal/ext-mem#docs/overview.md) is the next step up, an extension with state
and still no hardware.

## Notes

- `bm_hello()` has no arguments, no state and no side effects.
- Nothing else depends on ext-hello and it provides nothing.
