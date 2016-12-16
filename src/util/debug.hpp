/**
 * debug.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <string>

/* -- Macros -- */

/** Performs a compile-time static assertion. */
#define ogl_static_assert(cond)							\
  static_assert(cond, "Static assertion failed!")

#if defined(OGL_DEBUG)

/** Prints a trace message. */
#define ogl_trace()								\
  ogl_trace_message("")

/** Prints a trace message with a customizable string. */
#define ogl_trace_message(message)						\
  ogl::debug_message("ogl_trace", __PRETTY_FUNCTION__, __FILE__, __LINE__, message)

/** Prints an error message. */
#define ogl_error()								\
  ogl_error_message("")

/** Prints an error message with a customizable string. */
#define ogl_error_message(message)					        \
  ogl::error_message("ogl_error", __PRETTY_FUNCTION__, __FILE__, __LINE__, message)

/** Crashes the application. */
#define ogl_fail()								\
  ogl_fail_message("")

/** Crashes the application with a customizable string. */
#define ogl_fail_message(message)						\
  do										\
  {										\
    ogl_error_message(message);							\
    ogl::fail();								\
  }										\
  while (false)

/** Asserts that a condition is true, and crashes otherwise. */
#define ogl_assert(cond)							\
  if (!(cond)) ogl_fail_message(#cond)

#else

// Stub macros if OGL_DEBUG is not defined
#define ogl_trace()
#define ogl_trace_message(message)
#define ogl_error()
#define ogl_error_message(message)
#define ogl_fail()
#define ogl_fail_message(message)
#define ogl_assert(cond)

#endif /* defined(OGL_DEBUG) */

/* -- Procedure Prototypes -- */

namespace ogl
{

#if defined(OGL_DEBUG)

  /** Prints a trace message. */
  void debug_message(const std::string& title,
		     const std::string& func,
		     const std::string& file,
		     int line,
		     const std::string& message);

  /** Prints an error message. */
  void error_message(const std::string& title,
		     const std::string& func,
		     const std::string& file,
		     int line,
		     const std::string& message);

  /** Prints an error message and exits the app with a failure error code. */
  void fail() __attribute__((noreturn));

#endif /* defined(OGL_DEBUG) */

}
