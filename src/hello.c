/*
   +----------------------------------------------------------------------+
   | php-baremetal: ext-hello                                             |
   +----------------------------------------------------------------------+
   | Copyright (c) 2026 Gianfrancesco Aurecchia                           |
   +----------------------------------------------------------------------+
   | This source file is subject to the MIT license, that is bundled with |
   | this package in the file LICENSE.                                    |
   +----------------------------------------------------------------------+
   | Authors: Gianfrancesco Aurecchia <gianfri@aurecchia.com>             |
   +----------------------------------------------------------------------+
*/

/* A demo extension: bm_hello() returns a fixed greeting. */
#include "php.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_bm_hello, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(bm_hello)
{
    ZEND_PARSE_PARAMETERS_NONE();
    RETURN_STRING("hello from ext-hello package");
}

static const zend_function_entry hello_functions[] = {
    PHP_FE(bm_hello, arginfo_bm_hello)
    PHP_FE_END
};

zend_module_entry hello_module_entry = {
    STANDARD_MODULE_HEADER,
    "hello",
    hello_functions,
    NULL, NULL, NULL, NULL, NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};
