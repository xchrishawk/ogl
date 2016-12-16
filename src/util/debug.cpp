/**
 * debug.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>
#include <string>

#include "debug.hpp"

/* -- Constants -- */

namespace
{
  std::ostream& DEBUG_STREAM = std::cout;
  std::ostream& ERROR_STREAM = std::cerr;
}

/* -- Procedures -- */

void ogl::trace(const std::string& func,
		const std::string& file,
		int line,
		const std::string& message)
{
  DEBUG_STREAM << "* ogl_trace - " << func << " (" << file << ":" << line << ")" << std::endl;
  if (!message.empty())
    DEBUG_STREAM << "  " << message << std::endl;
}
