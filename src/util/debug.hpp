/**
 * @file	debug.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <iostream>
#include <string>

/* -- Macros -- */

/** Performs a compile-time static assertion. */
#define ogl_static_assert(cond, message)					\
  static_assert(cond, message)

#if defined(OGL_DEBUG)

#else

#endif

/* -- Procedure Prototypes -- */

namespace ogl
{

}

/* -- Procedures -- */

namespace ogl
{

}
