/**
 * @file	debug.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <string>

/* -- Macros -- */

/** Prints a message to the debug stream, even in release builds. */
#define ogl_debug_print_always(message)						\
  ogl::_debug_print(message)

/** Prints a message to the error stream, even in release builds. */
#define ogl_error_print_always(message)						\
  ogl::_error_print(message)

#if defined(OGL_DEBUG)

/** Prints a message to the debug stream. */
#define ogl_debug_print(message)						\
  ogl::_debug_print(message)

/** Prints a message to the error stream. */
#define ogl_error_print(message)						\
  ogl::_error_print(message)

/** Prints a trace message. */
#define ogl_trace()								\
  ogl::_trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, "")

/** Prints a trace message. */
#define ogl_trace_message(message)						\
  ogl::_trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, message)

/** Triggers a debugger breakpoint. */
#define ogl_breakpoint()							\
  ogl::_breakpoint(__PRETTY_FUNCTION__, __FILE__, __LINE__)

/** Asserts that `condition` is `true`. If not, prints an error message and fails. */
#define ogl_assert(condition)							\
  ((condition) ? ((void)0) : ogl::_fail_assert(__PRETTY_FUNCTION__, __FILE__, __LINE__, #condition, ""))

/** Asserts that `condition` is `true`. If not, prints an error message and fails. */
#define ogl_assert_message(condition, message)					\
  ((condition) ? ((void)0) : ogl::_fail_assert(__PRETTY_FUNCTION__, __FILE__, __LINE__, #condition, message))

/** Unconditionally fails an assert. */
#define ogl_assert_fail(message)					        \
  ogl::_fail_assert(__PRETTY_FUNCTION__, __FILE__, __LINE__, message, "")

#else

// Stub macros
#define ogl_debug_print(message)
#define ogl_error_print(message)
#define ogl_trace()
#define ogl_trace_message(message)
#define ogl_breakpoint()
#define ogl_assert(cond)
#define ogl_assert_message(cond, message)
#define ogl_assert_fail(message)

#endif

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Immediately and unconditionally crashes the application. */
  void fail() __attribute__((noreturn));

  /** Prints a message to the debug stream. */
  void _debug_print(const std::string& message);

  /** Prints a message to the error stream. */
  void _error_print(const std::string& message);

#if defined(OGL_DEBUG)

  /** Prints a trace message. */
  void _trace(const std::string& func,
	      const std::string& file,
	      int line,
	      const std::string& message);

  /** Triggers a debugger breakpoint. */
  void _breakpoint(const std::string& func,
		   const std::string& file,
		   int line);

  /** Fails an assertion. */
  void _fail_assert(const std::string& func,
		    const std::string& file,
		    int line,
		    const std::string& condition,
		    const std::string& message);

#endif /* defined(OGL_DEBUG) */

}
