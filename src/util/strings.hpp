/**
 * @file	strings.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <string>

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Creates a `std::string` using `printf`-like syntax. */
  std::string stringf(const std::string& format, ...);

}
