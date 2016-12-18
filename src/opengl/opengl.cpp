/**
 * @file	opengl.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl/api.hpp"
#include "opengl/error.hpp"
#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

opengl* opengl::s_instance = nullptr;

/* -- Procedures -- */

opengl::opengl()
{
  if (opengl::s_instance)
  {
    ogl_dbg_error("Attempted to initialize OpenGL while it was already initialized!");
    ogl::fail();
  }

#if defined(OGL_LINUX)

  // initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLFW!");

  // there is a bug where GLEW triggers an error on init. flush it from the queue.
  // http://stackoverflow.com/q/20034615/434245
  GLenum error __attribute__((unused)) = ogl::opengl_last_error();
  ogl_dbg_assert(error == GL_INVALID_ENUM);

#endif

  opengl::s_instance = this;
  ogl_dbg_status("OpenGL initialized.",
		 "API Version:        " + version(),
		 "GLSL Version:       " + glsl_version(),
		 "Vendor:             " + vendor(),
		 "Renderer:           " + renderer());
}

opengl::~opengl()
{
  opengl::s_instance = nullptr;
  ogl_dbg_status("OpenGL terminated.");
}

std::string opengl::version() const
{
  return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

std::string opengl::glsl_version() const
{
  return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

std::string opengl::vendor() const
{
  return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

std::string opengl::renderer() const
{
  return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}
