/**
 * @file	opengl.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl/api.hpp"
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
    ogl_error_print_always("Attempted to initialize OpenGL while it was already initialized!");
    ogl::fail();
  }

#if defined(OGL_LINUX)
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLFW!");
#endif

  opengl::s_instance = this;
  ogl_debug_print("OpenGL initialized.");
  print_version_info();
}

opengl::~opengl()
{
  opengl::s_instance = nullptr;
  ogl_debug_print("OpenGL terminated.");
}

void opengl::print_version_info()
{
#if defined(OGL_DEBUG)
  std::ostringstream output;
  output << "  API Version:    " << glGetString(GL_VERSION) << std::endl;
  output << "  GLSL Version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  output << "  Vendor:         " << glGetString(GL_VENDOR) << std::endl;
  output << "  Renderer:       " << glGetString(GL_RENDERER);
  ogl_debug_print(output.str());
#endif
}
