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

void ogl::fail()
{
  abort();
}

void ogl::_debug_print(const std::string& message)
{
  DEBUG_STREAM << message << std::endl;
}

void ogl::_error_print(const std::string& message)
{
  ERROR_STREAM << message << std::endl;
}

#if defined(OGL_DEBUG)

void ogl::_trace(const std::string& func,
		 const std::string& file,
		 int line,
		 const std::string& message)
{
  DEBUG_STREAM << "* ogl_trace - " << func << " (" << file << ":" << line << ")" << std::endl;
  if (!message.empty())
    DEBUG_STREAM << "  " << message << std::endl;
}

void ogl::_breakpoint(const std::string& func,
		      const std::string& file,
		      int line)
{
  ERROR_STREAM << "* ogl_breakpoint triggered - " << func << " (" << file << ":" << line << ")" << std::endl;
  raise(SIGINT);
}

void ogl::_fail_assert(const std::string& func,
		       const std::string& file,
		       int line,
		       const std::string& condition,
		       const std::string& message)
{
  ERROR_STREAM << "* ogl_assert FAILED - " << func << " (" << file << ":" << line << ")" << std::endl;
  if (!condition.empty())
    ERROR_STREAM << "  " << condition << std::endl;
  if (!message.empty())
    ERROR_STREAM << "  " << message << std::endl;

  ogl::fail();
}

#endif /* defined(OGL_DEBUG) */
