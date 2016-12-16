/**
 * glfw.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl/api.hpp"
#include "opengl/glfw/glfw.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

glfw::glfw()
{
  ogl_trace_message("GLFW initialized.");
}

glfw::~glfw()
{
  ogl_trace_message("GLFW shut down.");
}
