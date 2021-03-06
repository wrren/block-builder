<?php

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

// Try to load our extension if it's not already loaded.
if (!extension_loaded('block_creator')) {
  if (strtolower(substr(PHP_OS, 0, 3)) === 'win') {
    if (!dl('php_block_creator.dll')) return;
  } else {
    // PHP_SHLIB_SUFFIX gives 'dylib' on MacOS X but modules are 'so'.
    if (PHP_SHLIB_SUFFIX === 'dylib') {
      if (!dl('block_creator.so')) return;
    } else {
      if (!dl('block_creator.'.PHP_SHLIB_SUFFIX)) return;
    }
  }
}



abstract class block_creator {
	static function create_block($image_dir,$sheet,$image,$bound_width,$bound_height,$out_width,$out_height,$images,$image_count,$quality) {
		return create_block($image_dir,$sheet,$image,$bound_width,$bound_height,$out_width,$out_height,$images,$image_count,$quality);
	}
}

/* PHP Proxy Classes */

?>
