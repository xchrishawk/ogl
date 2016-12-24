/**
 * @file	debug.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <iostream>
#include <string>
#include <vector>

/* -- Macros -- */

/** Performs a compile-time static assertion. */
#define ogl_static_assert(cond, message)					\
  static_assert(cond, message)

#if defined(OGL_DEBUG)

/** Calls `ogl::fail()` if this is a debug build. */
#define ogl_dbg_fail()								\
  ogl::fail()

/** Calls `ogl::breakpoint()` if this is a debug build. */
#define ogl_dbg_breakpoint()							\
  ogl::breakpoint()

/** Prints a status message to the debug stream. */
#define ogl_dbg_status(...)							\
  do										\
  {										\
    ogl::debug_stream() << ogl::debug_message("ogl_dbg_status",			\
					      __PRETTY_FUNCTION__,		\
					      __FILE__,				\
					      __LINE__,				\
					      { __VA_ARGS__ })			\
			<< std::endl;						\
  }										\
  while (false)

/** Prints a warning message to the debug stream. */
#define ogl_dbg_warning(...)							\
  do										\
  {										\
    ogl::error_stream() << ogl::debug_message("ogl_dbg_warning",		\
					      __PRETTY_FUNCTION__,		\
					      __FILE__,				\
					      __LINE__,				\
					      { __VA_ARGS__ })			\
			<< std::endl;						\
  }										\
  while (false)

/** Prints an error message to the debug stream. */
#define ogl_dbg_error(...)							\
  do										\
  {										\
    ogl::error_stream() << ogl::debug_message("ogl_dbg_error",			\
					      __PRETTY_FUNCTION__,		\
					      __FILE__,				\
					      __LINE__,				\
					      { __VA_ARGS__ })			\
			<< std::endl;						\
  }										\
  while (false)

/** Asserts that `cond` is true, and calls `ogl::fail()` if not. */
#define ogl_dbg_assert(cond)							\
  do										\
  {										\
    if (!(cond))								\
    {										\
      ogl::error_stream() << ogl::debug_message("ogl_assert FAILED",		\
						__PRETTY_FUNCTION__,		\
						__FILE__,			\
						__LINE__,			\
						{ "failed: " #cond })		\
			  << std::endl;						\
      ogl::breakpoint();							\
      ogl::fail();								\
    }										\
  }										\
  while (false)

/** Unconditionally fails an assert. */
#define ogl_dbg_assert_fail(message)						\
  do										\
  {										\
    ogl::error_stream() << ogl::debug_message("ogl_assert FAILED",		\
					      __PRETTY_FUNCTION__,		\
					      __FILE__,				\
					      __LINE__,				\
					      { message })			\
			<< std::endl;						\
    ogl::breakpoint();								\
    ogl::fail();								\
  }										\
  while (false)

#else

// Stub macros
#define ogl_dbg_fail()
#define ogl_dbg_breakpoint()
#define ogl_dbg_status(...)
#define ogl_dbg_warning(...)
#define ogl_dbg_error(...)
#define ogl_dbg_assert(cond)
#define ogl_dbg_assert_fail(message)

#endif

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Immediately and unconditionally crashes the application. */
  void fail() __attribute__((noreturn));

  /** Triggers a platform-specific debugger breakpoint. */
  void breakpoint();

  /** Returns the stream that should be used for debug output. */
  constexpr std::ostream& debug_stream()
  {
    return std::cout;
  }

  /** Returns the stream that should be used for error output. */
  constexpr std::ostream& error_stream()
  {
    return std::cerr;
  }

  /**
   * Returns a formatted debug message as a string.
   *
   * @param title
   * The title of the alert.
   *
   * @param function
   * The name of the function that generated the alert.
   *
   * @param file
   * The name of the file that generated the alert.
   *
   * @param line
   * The line number that generated the alert.
   *
   * @param message
   * A `std::vector` of `std::string`s which will be printed as additional lines
   * at the end of the message.
   */
  std::string debug_message(const std::string& title,
			    const std::string& function,
			    const std::string& file,
			    int line,
			    const std::vector<std::string>& messages = { });

}
