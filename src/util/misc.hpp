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
   * Returns the number of elements in an enum.
   *
   * @note
   * The enum must have a member named `count` representing the total number of
   * elements in the enum.
   */
  template<typename T>
  constexpr size_t enum_count()
  {
    return static_cast<size_t>(T::count);
  }

}
