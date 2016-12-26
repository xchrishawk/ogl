/**
 * @file	opengl.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <string>
#include <GL/glew.h>

#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  /** Returns an OpenGL string. */
  std::string get_opengl_string(GLenum name);

  /** Converts a `GLenum` to an `opengl_error`. */
  opengl_error glenum_to_opengl_error(GLenum error);
}

/* -- Procedures -- */

std::string opengl::version() const
{
  return get_opengl_string(GL_VERSION);
}

std::string opengl::glsl_version() const
{
  return get_opengl_string(GL_SHADING_LANGUAGE_VERSION);
}

std::string opengl::vendor() const
{
  return get_opengl_string(GL_VENDOR);
}

std::string opengl::renderer() const
{
  return get_opengl_string(GL_RENDERER);
}

ogl::opengl_error opengl::last_error() const
{
  opengl_error last_error = opengl_error::no_error;
  opengl_error this_error = opengl_error::no_error;

  while ((this_error = glenum_to_opengl_error(glGetError())) != opengl_error::no_error)
  {
#if defined(OGL_DEBUG)
    if (last_error != opengl_error::no_error)
    {
      // this error is going to be swallowed, so print a warning about it so it's not lost
      ogl_dbg_warning("Suppressing OpenGL error: " + error_string(last_error));
    }
#endif /* defined(OGL_DEBUG) */
    last_error = this_error;
  }

  return last_error;
}

std::string opengl::error_string(ogl::opengl_error error) const
{
  switch (error)
  {
  case opengl_error::no_error:
    return "GL_NO_ERROR";
  case opengl_error::invalid_enum:
    return "GL_INVALID_ENUM";
  case opengl_error::invalid_value:
    return "GL_INVALID_VALUE";
  case opengl_error::invalid_operation:
    return "GL_INVALID_OPERATION";
  case opengl_error::invalid_framebuffer_operation:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case opengl_error::out_of_memory:
    return "GL_OUT_OF_MEMORY";
  case opengl_error::stack_underflow:
    return "GL_STACK_UNDERFLOW";
  case opengl_error::stack_overflow:
    return "GL_STACK_OVERFLOW";
  default: // includes opengl_error::unknown
    ogl_dbg_assert_fail("Unknown error!");
    return "Unknown Error";
  }
}

/* -- Private Procedures -- */

namespace
{
  std::string get_opengl_string(GLenum name)
  {
    return std::string(reinterpret_cast<const char*>(glGetString(name)));
  }

  opengl_error glenum_to_opengl_error(GLenum error)
  {
    switch (error)
    {
    case GL_NO_ERROR:
      return opengl_error::no_error;
    case GL_INVALID_ENUM:
      return opengl_error::invalid_enum;
    case GL_INVALID_VALUE:
      return opengl_error::invalid_value;
    case GL_INVALID_OPERATION:
      return opengl_error::invalid_operation;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return opengl_error::invalid_framebuffer_operation;
    case GL_OUT_OF_MEMORY:
      return opengl_error::out_of_memory;
    case GL_STACK_OVERFLOW:
      return opengl_error::stack_overflow;
    case GL_STACK_UNDERFLOW:
      return opengl_error::stack_underflow;
    default:
      ogl_dbg_assert_fail("Unknown error!");
      return opengl_error::unknown;
    }
  }
}
