/**
 * @file	opengl_interface.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

#include "opengl/api.hpp"
#include "opengl/opengl.hpp"
#include "opengl/impl/opengl_buffer.hpp"
#include "opengl/impl/opengl_interface.hpp"
#include "opengl/impl/opengl_program.hpp"
#include "opengl/impl/opengl_shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;
using namespace ogl::impl;

/* -- Variables -- */

opengl_interface* opengl_interface::s_instance = nullptr;

/* -- Procedure Prototypes -- */

namespace
{
  std::string get_opengl_string(GLenum name);
}

/* -- Procedures -- */

ogl::opengl::ptr opengl_interface::create()
{
  return ogl::opengl::ptr(new opengl_interface());
}

opengl_interface::opengl_interface()
  : opengl()
{
  if (opengl_interface::s_instance)
  {
    ogl_dbg_error("Attempted to initialize OpenGL while it is already initialized!");
    ogl::fail();
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw opengl_exception("Failed to initialize GLEW.");

  // there is a bug where GLEW triggers an error on init. flush it from the queue.
  // http://stackoverflow.com/q/20034615/434245
  GLenum error __attribute__((unused)) = last_error();
  ogl_dbg_assert(error == GL_INVALID_ENUM);

  opengl_interface::s_instance = this;
  ogl_dbg_status("OpenGL initialized.",
		 "API Version:\t\t" + version(),
		 "GLSL Version:\t\t" + glsl_version(),
		 "Vendor:\t\t" + vendor(),
		 "Renderer:\t\t" + renderer(),
		 "Loader:\t\tGLEW");
}

opengl_interface::~opengl_interface()
{
  opengl_interface::s_instance = nullptr;
  ogl_dbg_status("OpenGL terminated.");
}

shader::ptr opengl_interface::create_shader(GLenum type) const
{
  return opengl_shader::create(type);
}

program::ptr opengl_interface::create_program() const
{
  return opengl_program::create();
}

buffer::ptr opengl_interface::create_immutable_buffer(GLenum type,
						      const void* data,
						      size_t size,
						      GLbitfield flags) const
{
  ogl_dbg_error("Not yet implemented!");
  ogl::fail();
}

std::string opengl_interface::version() const
{
  return get_opengl_string(GL_VERSION);
}

std::string opengl_interface::glsl_version() const
{
  return get_opengl_string(GL_SHADING_LANGUAGE_VERSION);
}

std::string opengl_interface::vendor() const
{
  return get_opengl_string(GL_VENDOR);
}

std::string opengl_interface::renderer() const
{
  return get_opengl_string(GL_RENDERER);
}

GLenum opengl_interface::last_error() const
{
  GLenum last_error = GL_NO_ERROR;
  GLenum this_error = GL_NO_ERROR;

  while ((this_error = glGetError()) != GL_NO_ERROR)
  {
#if defined(OGL_DEBUG)
    if (last_error != GL_NO_ERROR)
    {
      // this error is going to be swallowed, so print a warning about it so it's not lost
      ogl_dbg_warning("Suppressing OpenGL error: " + error_string(last_error));
    }
#endif /* defined(OGL_DEBUG) */
    last_error = this_error;
  }

  return last_error;
}

std::string opengl_interface::error_string(GLenum error) const
{
  switch (error)
  {
  case GL_NO_ERROR:
    return "GL_NO_ERROR";
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY";
  case GL_STACK_UNDERFLOW:
    return "GL_STACK_UNDERFLOW";
  case GL_STACK_OVERFLOW:
    return "GL_STACK_OVERFLOW";
  default:
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
}
