/**
 * @file	glew.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>
#include <GL/glew.h>

#include "glew/glew.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

glew* glew::s_instance = nullptr;

/* -- Procedures -- */

glew::glew()
{
  if (glew::s_instance)
  {
    ogl_error_print_always("Attempted to initialize GLEW while it was already initialized!");
    ogl::fail();
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW!");

  glew::s_instance = this;
  ogl_debug_print("GLEW initialized.");
}

glew::~glew()
{
  glew::s_instance = nullptr;
  ogl_debug_print("GLEW terminated.");
}
