/**
 * window.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl/api.hpp"
#include "opengl/glfw/window.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

window::window()
{
  ogl_trace_message("GLFW window created.");
}

window::~window()
{
  ogl_trace_message("GLFW window destroyed.");
}
