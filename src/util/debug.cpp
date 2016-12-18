/**
 * @file	debug.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <csignal>
#include <cstdlib>
#include <iostream>

#include "util/debug.hpp"

/* -- Constants -- */

namespace
{
  std::ostream& DEBUG_STREAM = std::cerr;
  std::ostream& ERROR_STREAM = std::cerr;
}

/* -- Procedures -- */
