/**
 * @file	opengl.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <string>
#include <GL/glew.h>

#include "opengl.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  /** Returns an OpenGL string. */
  std::string get_opengl_string(GLenum name);
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

/* -- Private Procedures -- */

namespace
{
   std::string get_opengl_string(GLenum name)
   {
     return std::string(reinterpret_cast<const char*>(glGetString(name)));
   }
}
