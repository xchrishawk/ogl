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

/* -- Procedures -- */

namespace ogl
{

  /** Clamps a `float` between a minimum and maximum value. */
  inline float clamp(float value, float minimum, float maximum)
  {
    if (value < minimum)
      return minimum;
    else if (value > maximum)
      return maximum;
    else
      return value;
  }

}
