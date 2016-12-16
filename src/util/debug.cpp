/**
 * @file	debug.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#if defined(OGL_DEBUG)

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

/* -- Procedure Prototypes -- */

namespace
{

  void print_message(std::ostream& stream,
		     const std::string& title,
		     const std::string& func,
		     const std::string& file,
		     int line,
		     const std::string& message);

}

/* -- Procedures -- */

void ogl::debug_message(const std::string& title,
			const std::string& func,
			const std::string& file,
			int line,
			const std::string& message)
{
  print_message(DEBUG_STREAM, title, func, file, line, message);
}

void ogl::error_message(const std::string& title,
			const std::string& func,
			const std::string& file,
			int line,
			const std::string& message)
{
  print_message(ERROR_STREAM, title, func, file, line, message);
}

void ogl::fail()
{
  abort();
}

namespace
{

  void print_message(std::ostream& stream,
		     const std::string& title,
		     const std::string& func,
		     const std::string& file,
		     int line,
		     const std::string& message)
  {
    stream << "* " << title << " - " << func << " (" << file << ":" << line << ")" << std::endl;
    if (!message.empty())
      stream << "  " << message << std::endl;
  }

}

#endif /* defined(OGL_DEBUG) */
