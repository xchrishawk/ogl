/**
 * @file	error.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <sstream>
#include <string>

#include "opengl/error.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

GLenum ogl::opengl_last_error()
{
  GLenum last_error = GL_NO_ERROR;
  GLenum this_error = GL_NO_ERROR;

  while ((this_error = glGetError()) != GL_NO_ERROR)
  {
    // if we have to swallow an error, report it to the console
    if (last_error != GL_NO_ERROR)
    {
      ogl_dbg_warning("Ignoring OpenGL error because there are additional errors in the queue!",
		      opengl_error_string(last_error));
    }
    last_error = this_error;
  }

  return last_error;
}

std::string ogl::opengl_error_string(GLenum error)
{
  switch (error)
  {
  case GL_NO_ERROR:
    return "No Error";
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM (0x0500)";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE (0x0501)";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION (0x0502)";
  case GL_STACK_OVERFLOW:
    return "GL_STACK_OVERFLOW (0x0503)";
  case GL_STACK_UNDERFLOW:
    return "GL_STACK_UNDERFLOW (0x0504)";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY (0x0505)";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION (0x0506)";
  default:
    ogl_dbg_assert_fail("Unknown OpenGL error code!");
    return "Unknown Error";
  }
}

#if defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR)

void ogl::_opengl_check_error(const std::string& func,
			      const std::string& file,
			      int line)
{
  GLenum error = opengl_last_error();
  if (error != GL_NO_ERROR)
  {
    std::string message = ogl::debug_message("ogl_opengl_check_error",
					     func,
					     file,
					     line,
					     { "Unexpected OpenGL error!", opengl_error_string(error) });
    ogl::error_stream() << message << std::endl;
    ogl_breakpoint();
  }
}

#endif /* defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR) */
