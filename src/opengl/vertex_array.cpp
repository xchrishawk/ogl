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

void vertex_array::unactivate()
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
}

void vertex_array::activate() const
{
  glBindVertexArray(m_handle);
}

void vertex_array::vertex_buffer_format(GLuint binding_index,
					GLuint attribute_index,
					GLint size,
					GLint relative_offset)
{
  // set format of the attribute
  glVertexArrayAttribFormat(m_handle,			// vaobj
			    attribute_index,		// attribindex
			    size,			// size
			    GL_FLOAT,			// type
			    GL_FALSE,			// normalized
			    relative_offset);		// relative offset

  // associate the attribute with the buffer binding
  glVertexArrayAttribBinding(m_handle,			// vaobj
			     attribute_index,		// attribindex
			     binding_index);		// bindingindex

  // enable array access for the attribute
  glEnableVertexArrayAttrib(m_handle,			// vaobj
			    attribute_index);		// attribindex
}

void vertex_array::activate_vertex_buffer(GLuint binding_index,
					  immutable_buffer::ptr buffer,
					  GLsizei stride,
					  GLintptr offset)
{
  glVertexArrayVertexBuffer(m_handle,			// vaobj
			    binding_index,		// bindingindex
			    buffer->handle(),		// buffer
			    offset,			// offset
			    stride);			// stride
}

void vertex_array::unactivate_vertex_buffer(GLuint binding_index)
{
  glVertexArrayVertexBuffer(m_handle,			// vaobj
			    binding_index,		// bindingindex
			    0,				// buffer
			    0,				// offset
			    0);				// stride
}

GLuint vertex_array::new_handle()
{
  GLuint handle = 0;
  glCreateVertexArrays(1, &handle);
  if (handle == 0)
    opengl_throw_last_error("Failed to create vertex array.");
  return handle;
}
