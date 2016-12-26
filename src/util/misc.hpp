/**
 * @file	misc.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <cstdlib>

/* -- Procedures -- */

namespace ogl
{

  /**
   * Returns the size of the specified array.
   */
  template <typename T, size_t size>
  constexpr size_t array_size(const T (&)[size])
  {
    return size;
  }

  /**
   * Returns the number of elements in an enum.
   *
   * @note
   * The enum must have a member named `count` representing the total number of
   * elements in the enum.
   */
  template <typename T>
  constexpr size_t enum_count()
  {
    return static_cast<size_t>(T::count);
  }

  /** Clamps `value` between `minimum` and `maximum`. */
  template <typename T>
  inline T clamp(T value, T minimum, T maximum)
  {
    if (value < minimum)
      return minimum;
    else if (value > maximum)
      return maximum;
    else
      return value;
  }

}
