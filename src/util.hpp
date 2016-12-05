/**
 * util.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef UTIL_HPP
#define UTIL_HPP

/* -- Includes -- */

#include <string>

/* -- Macros -- */

/** Static assert macro. */
#define ogl_static_assert(cond, message)					\
  static_assert(cond, message)

/** Macro to get size of an array. */
#define ogl_array_size(array)							\
  (sizeof(array) / sizeof(array[0]))

#ifdef OGL_DEBUG

/** Asserts that a condition is true and fails otherwise. */
#define ogl_assert(cond)							\
  ((cond) ? (void) 0 : ogl::_ogl_fail(__PRETTY_FUNCTION__, __FILE__, __LINE__, #cond))

/** Prints a trace message. */
#define ogl_trace()								\
  ogl::_ogl_trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, "")

/** Prints a trace message with a custom string. */
#define ogl_trace_message(message)						\
  ogl::_ogl_trace(__PRETTY_FUNCTION__, __FILE__, __LINE__, message)

/** Prints an error message. */
#define ogl_error()								\
  ogl::_ogl_error(__PRETTY_FUNCTION__, __FILE__, __LINE__, "")

/** Prints an error message with a custom string. */
#define ogl_error_message(message)						\
  ogl::_ogl_error(__PRETTY_FUNCTION__, __FILE__, __LINE__, message)

/** Triggers a debugger breakpoint. */
#define ogl_break()								\
  ogl::_ogl_break()

#else

#define ogl_assert(cond)
#define ogl_trace()
#define ogl_trace_message()
#define ogl_break()

#endif /* OGL_DEBUG */

/* -- Procedure Prototypes -- */

namespace ogl
{

#ifdef OGL_DEBUG

  /** Implementation for ogl_assert failures. */
  void _ogl_fail(const std::string& func, const std::string& file, int line, const std::string& message)
    __attribute__((noreturn));

  /** Implementation for ogl_trace. */
  void _ogl_trace(const std::string& func, const std::string& file, int line, const std::string& message);

  /** Implementation for ogl_error. */
  void _ogl_error(const std::string& func, const std::string& file, int line, const std::string& message);

  /** Implementation for ogl_break. */
  void _ogl_break();

#endif

}

#endif /* UTIL_HPP */
