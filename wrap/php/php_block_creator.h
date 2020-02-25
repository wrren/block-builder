/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef PHP_BLOCK_CREATOR_H
#define PHP_BLOCK_CREATOR_H

extern zend_module_entry block_creator_module_entry;
#define phpext_block_creator_ptr &block_creator_module_entry

#ifdef PHP_WIN32
# define PHP_BLOCK_CREATOR_API __declspec(dllexport)
#else
# define PHP_BLOCK_CREATOR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(block_creator);
PHP_MSHUTDOWN_FUNCTION(block_creator);
PHP_RINIT_FUNCTION(block_creator);
PHP_RSHUTDOWN_FUNCTION(block_creator);
PHP_MINFO_FUNCTION(block_creator);

ZEND_NAMED_FUNCTION(_wrap_create_block);
#endif /* PHP_BLOCK_CREATOR_H */
