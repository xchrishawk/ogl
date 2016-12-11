/**
 * misc.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_UTIL_MISC_HPP
#define OGL_UTIL_MISC_HPP

/* -- Macros -- */

/** Macro returning the size of an array. */
#define ogl_array_size(array)							\
  (sizeof(array) / sizeof(array[0]))

/* -- Procedure Prototypes -- */

namespace ogl
{
  int ogl_rand();
  float ogl_randf();
  double ogl_randd();
}

#endif /* OGL_UTIL_MISC_HPP */
