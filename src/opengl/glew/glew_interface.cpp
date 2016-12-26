/**
 * @file	glew_interface.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

#include <GL/glew.h>

#include "opengl/opengl.hpp"
#include "opengl/glew/glew_interface.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl::glew;

/* -- Variables -- */

glew_interface* glew_interface::s_instance = nullptr;

/* -- Procedures -- */

ogl::opengl::ptr glew_interface::create()
{
  return ogl::opengl::ptr(new glew_interface());
}

glew_interface::glew_interface()
  : opengl()
{
  if (glew_interface::s_instance)
  {
    ogl_dbg_error("Attempted to initialize OpenGL while it is already initialized!");
    ogl::fail();
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW.");

  // there is a bug where GLEW triggers an error on init. flush it from the queue.
  // http://stackoverflow.com/q/20034615/434245
  opengl_error error __attribute__((unused)) = last_error();
  ogl_dbg_assert(error == opengl_error::invalid_enum);

  glew_interface::s_instance = this;
  ogl_dbg_status("OpenGL initialized.",
		 "API Version:\t\t" + version(),
		 "GLSL Version:\t\t" + glsl_version(),
		 "Vendor:\t\t" + vendor(),
		 "Renderer:\t\t" + renderer(),
		 "Loader:\t\tGLEW");
}

glew_interface::~glew_interface()
{
  glew_interface::s_instance = nullptr;
  ogl_dbg_status("OpenGL terminated.");
}
