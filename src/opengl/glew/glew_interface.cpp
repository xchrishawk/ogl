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

/* -- Procedure Prototypes -- */

namespace
{
  std::string get_opengl_string(GLenum name);
}

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

std::string glew_interface::version() const
{
  return get_opengl_string(GL_VERSION);
}

std::string glew_interface::glsl_version() const
{
  return get_opengl_string(GL_SHADING_LANGUAGE_VERSION);
}

std::string glew_interface::vendor() const
{
  return get_opengl_string(GL_VENDOR);
}

std::string glew_interface::renderer() const
{
  return get_opengl_string(GL_RENDERER);
}

/* -- Private Procedures -- */

namespace
{
   std::string get_opengl_string(GLenum name)
   {
     return std::string(reinterpret_cast<const char*>(glGetString(name)));
   }
}
