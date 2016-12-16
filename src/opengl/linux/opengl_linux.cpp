/**
 * opengl_linux.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl/linux/opengl_linux.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

opengl_linux::opengl_linux()
  : m_glew()
{
  ogl_trace_message("OpenGL initialized.");
}

opengl_linux::~opengl_linux()
{
  ogl_trace_message("OpenGL shut down.");
}
