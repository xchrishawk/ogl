/**
 * debug.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <string>

/* -- Macros -- */

#if defined(OGL_DEBUG)

/** Prints a trace message. */
#define ogl_trace()								\
  ogl::trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, "")

/** Prints a trace message with a customizable string. */
#define ogl_trace_message(message)						\
  ogl::trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, message)

#else

// Stub macros if OGL_DEBUG is not defined
#define ogl_trace()
#define ogl_trace_message(message)

#endif

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Prints a trace message. */
  void trace(const std::string& func,
	     const std::string& file,
	     int line,
	     const std::string& message);

}
