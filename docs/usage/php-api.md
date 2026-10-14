---
eyebrow: 'ext-hello · PHP API'
lede:    'The whole PHP surface of ext-hello: one function that returns a fixed string. No arguments, no state, no side effects.'
see_also:
  - { href: '../overview.md', meta: 'Overview' }
  - { href: '../recipes/check-the-build.md', meta: 'Recipe' }
prev: { label: 'Overview', href: '../overview.md' }
next: { label: 'Check that a package is built in', href: '../recipes/check-the-build.md' }
---

# PHP API

The extension registers under the module name `hello` and adds a single global function.

## bm_hello

<!-- @method name="bm_hello(): string" returns="string" visibility="public" -->

Returns the string `"hello from ext-hello package"`. It takes no arguments; passing any throws an
`ArgumentCountError`.

<!-- @code-block language="php" label="project-src/index.php" -->
```php
<?php
var_dump(bm_hello());       // string(28) "hello from ext-hello package"
```
<!-- @endcode-block -->

## Checking it is there

A firmware built without the package has no `bm_hello()`. Guard optional use with `extension_loaded()` or
`function_exists()`, so the same script runs on both:

<!-- @code-block language="php" label="guarded call" -->
```php
<?php
if (extension_loaded('hello')) {
    echo bm_hello(), "\n";
} else {
    echo "ext-hello is not built in\n";
}
```
<!-- @endcode-block -->
