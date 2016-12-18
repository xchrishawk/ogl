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
    ogl_error_print_always("Attempted to initialize OpenGL while it was already initialized!");
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
  ogl_assert_message(error == GL_INVALID_ENUM, "Unexpected GLEW init error!");

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
