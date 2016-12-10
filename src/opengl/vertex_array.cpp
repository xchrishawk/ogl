/**
 * vertex_array.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl/error.hpp"
#include "opengl/vertex_array.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

vertex_array::ptr vertex_array::create()
{
  return vertex_array::ptr(new vertex_array());
}

void vertex_array::unbind()
{
  glBindVertexArray(0);
}

vertex_array::vertex_array()
  : m_handle(vertex_array::new_handle())
{
}

vertex_array::~vertex_array()
{
  glDeleteVertexArrays(1, &m_handle);
  ogl_trace();
}

void vertex_array::bind() const
{
  glBindVertexArray(m_handle);
}

GLuint vertex_array::new_handle()
{
  GLuint handle = 0;
  glCreateVertexArrays(1, &handle);
  if (handle == 0)
    opengl_throw_last_error("Failed to create vertex array.");
  return handle;
}
