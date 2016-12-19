/**
 * @file	misc.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Macros -- */

/** Returns the size of a statically-defined array. */
#define ogl_array_size(array)							\
  (sizeof(array) / sizeof(array[0]))
