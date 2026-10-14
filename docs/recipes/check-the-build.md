---
eyebrow: 'ext-hello · Recipe'
lede:    'Require ext-hello, flash, and read one line on the serial console: the fastest check that your project builds the packages it requires.'
see_also:
  - { href: '../overview.md', meta: 'Overview' }
  - { href: '../usage/php-api.md', meta: 'PHP API' }
prev: { label: 'PHP API', href: '../usage/php-api.md' }
next: { label: 'No next page', href: '#' }
---

# Check that a package is built in

Before wiring hardware, make sure the package pipeline works: a package you require ends up in the firmware and its
functions are callable from your script. ext-hello needs nothing else, so if it does not show up, the problem is
the project setup, not a missing provider. Remove it from the project afterwards.

## Goal

Print the greeting from `bm_hello()` on the serial console, and list the extensions the firmware actually
contains.

## The steps

<!-- @steps -->
- **Require the package**

  From the project: `composer require php-baremetal/ext-hello`.

- **Build and flash**

  `phpbm flash`, as for any change to the project's packages.

- **Run the script and open the console**

  Put the code below in `project-src/index.php`, then `phpbm monitor`.
<!-- @endsteps -->

## The code

<!-- @code-block language="php" label="project-src/index.php" -->
```php
<?php
echo extension_loaded('hello') ? bm_hello() : 'ext-hello missing', "\n";

// Every extension compiled into this firmware.
echo implode(', ', get_loaded_extensions()), "\n";

function loop(int $tick): void
{
    delay(1000);
}
```
<!-- @endcode-block -->

Expected output; the extension list depends on what your project requires, and `hello` must be in it:

<!-- @code-block language="text" label="serial console" -->
```text
hello from ext-hello package
Core, date, ..., hello, ...
```
<!-- @endcode-block -->

<!-- @callout variant="tip" title="If it says missing" -->
Check that `php-baremetal/conductor` is in the project's `require` and allowed under `config.allow-plugins`, that
`composer install` ran after the `require`, and that the board was reflashed with the new build.
<!-- @endcallout -->
