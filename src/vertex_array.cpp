/**
 * vertex_array.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl.hpp"
#include "util.hpp"
#include "vertex_array.hpp"

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
  : m_id(0)
{
  glCreateVertexArrays(1, &m_id);
  if (m_id == 0)
  {
    GLenum error = opengl_last_error();
    ostringstream message;
    message << "Failed to create vertex array. " << opengl_error_string(error);
    throw runtime_error(message.str());
  }
}

vertex_array::vertex_array(GLuint id)
  : m_id(id)
{
}

vertex_array::~vertex_array()
{
  glDeleteVertexArrays(1, &m_id);
}

void vertex_array::bind() const
{
  glBindVertexArray(m_id);
}
