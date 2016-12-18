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
#if defined(OGL_DEBUG)
    if (last_error != GL_NO_ERROR)
    {
      // this error is getting swallowed, so report it
      std::ostringstream message;
      message << "* Ignoring OpenGL error because there are additional errors in the queue!" << std::endl;
      message << "  " << opengl_error_string(last_error);
      ogl_error_print(message.str());
    }
#endif
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
    return "OpenGL Error 0x0500 (GL_INVALID_ENUM)";
  case GL_INVALID_VALUE:
    return "OpenGL Error 0x0501 (GL_INVALID_VALUE)";
  case GL_INVALID_OPERATION:
    return "OpenGL Error 0x0502 (GL_INVALID_OPERATION)";
  case GL_STACK_OVERFLOW:
    return "OpenGL Error 0x0503 (GL_STACK_OVERFLOW)";
  case GL_STACK_UNDERFLOW:
    return "OpenGL Error 0x0504 (GL_STACK_UNDERFLOW)";
  case GL_OUT_OF_MEMORY:
    return "OpenGL Error 0x0505 (GL_OUT_OF_MEMORY)";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "OpenGL Error 0x0506 (GL_INVALID_FRAMEBUFFER_OPERATION)";
  default:
    ogl_assert_fail("Unknown OpenGL error code!");
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
    std::ostringstream message;
    message << "* ogl_opengl_check_error - " << func << " (" << file << ":" << line << ")" << std::endl;
    message << "  Unexpected OpenGL error: " << opengl_error_string(error);

    ogl_error_print(message.str());
    ogl_breakpoint();
  }
}

#endif /* defined(OGL_DEBUG_BREAK_ON_OPENGL_ERROR) */
