/**
 * @file	debug.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <ostream>
#include <string>
#include <vector>

/* -- Debug Macros -- */

#if defined(OGL_DEBUG)

/** Calls `ogl::debug::fail()` if this is a debug build. */
#define ogl_dbg_fail()								\
  ogl::debug::fail()

/** Calls `ogl::debug::breakpoint()` if this is a debug build. */
#define ogl_dbg_breakpoint()							\
  ogl::debug::breakpoint()

/** Prints a status debug message to the debug stream. */
#define ogl_dbg_status(...)							\
  do										\
  {										\
    ogl::debug::debug_stream()							\
      << ogl::debug::trace_message("ogl_dbg_status",				\
                                   __PRETTY_FUNCTION__,				\
                                   __FILE__,					\
                                   __LINE__,					\
                                   { __VA_ARGS__ })				\
      << std::endl;								\
  }										\
  while (false)

/** Prints a warning debug message to the debug stream. */
#define ogl_dbg_warning(...)							\
  do										\
  {										\
    ogl::debug::debug_stream()							\
      << ogl::debug::trace_message("ogl_dbg_warning",				\
                                   __PRETTY_FUNCTION__,				\
                                   __FILE__,					\
                                   __LINE__,					\
                                   { __VA_ARGS__ })				\
      << std::endl;								\
  }										\
  while (false)

/** Prints an error debug message to the debug stream. */
#define ogl_dbg_error(...)							\
  do										\
  {										\
    ogl::debug::error_stream()							\
      << ogl::debug::trace_message("ogl_dbg_error",				\
                                   __PRETTY_FUNCTION__,				\
                                   __FILE__,					\
                                   __LINE__,					\
                                   { __VA_ARGS__ })				\
      << std::endl;								\
  }										\
  while (false)

#else

#define ogl_dbg_fail()
#define ogl_dbg_breakpoint()
#define ogl_dbg_status(...)
#define ogl_dbg_warning(...)
#define ogl_dbg_error(...)

#endif

/* -- Assert Macros -- */

#if !defined(OGL_NOASSERT)

/** Performs an assertion, and fails the application if the assertion does not pass. */
#define ogl_assert(cond)							\
  do										\
  {										\
    if ((cond))									\
      break;									\
    ogl::debug::error_stream()							\
      << ogl::debug::trace_message("ogl_assert FAILED",				\
                                   __PRETTY_FUNCTION__,				\
                                   __FILE__,					\
                                   __LINE__,					\
                                   { #cond })					\
      << std::endl;								\
    ogl::debug::fail();								\
  }										\
  while (false)

/** Unconditionally fails an assert. */
#define ogl_assert_fail(message)						\
  do										\
  {										\
    ogl::debug::error_stream()							\
      << ogl::debug::trace_message("ogl_assert FAILED",				\
                                   __PRETTY_FUNCTION__,				\
                                   __FILE__,					\
                                   __LINE__,					\
                                   { message })					\
      << std::endl;								\
    ogl::debug::fail();								\
  }										\
  while (false)

#else

#define ogl_assert(cond)
#define ogl_assert_fail(message)

#endif

/* -- Types -- */

namespace ogl
{

  /**
   * Class containing utility functions for debugging purposes.
   */
  class debug
  {
  public:

    /** Immediately crashes the application. */
    static void fail() __attribute__((noreturn));

    /** Triggers a platform-specific breakpoint. */
    static void breakpoint();

    /** The output stream to use for debug printing. */
    static std::ostream& debug_stream()
    { return *debug_stream_; }

    /** The output stream to use for error printing. */
    static std::ostream& error_stream()
    { return *error_stream_; }

    /** Returns a trace message string with the specified parameters. */
    static std::string trace_message(const std::string& title,
				     const std::string& function,
				     const std::string& file,
				     int line,
				     const std::vector<std::string>& messages);

  private:

    static std::ostream* const debug_stream_;
    static std::ostream* const error_stream_;

    debug() = delete;
    debug(const debug&) = delete;
    debug& operator =(const debug&) = delete;

  };

}
