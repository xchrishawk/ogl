/**
 * glew.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl/api.hpp"
#include "opengl/linux/glew.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

glew::glew()
{
  ogl_trace_message("GLEW initialized.");
}

glew::~glew()
{
  ogl_trace_message("GLEW shut down.");
}
