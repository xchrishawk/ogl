/**
 * @file	error.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

// Uncomment this line to break when an OpenGL error occurs
// #define OGL_DEBUG_BREAK_ON_OPENGL_ERROR

/* -- Includes -- */

#include <string>
#include "opengl/api.hpp"

/* -- Macros -- */

#if defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR)

/** Checks for OpenGL errors, and triggers a breakpoint if one has occurred. */
#define ogl_opengl_check_error() 						\
  ogl::_opengl_check_error(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#else

// Stub macro
#define ogl_opengl_check_error()

#endif

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Returns the last OpenGL error in the queue, if one exists. */
  GLenum opengl_last_error();

  /** Returns a string for the specified OpenGL error code. */
  std::string opengl_error_string(GLenum error);

#if defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR)

  /** Checks for OpenGL errors, and triggers a breakpoint if one occurs. */
  void _opengl_check_error(const std::string& func,
			   const std::string& file,
			   int line);

#endif /* defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR) */

}
