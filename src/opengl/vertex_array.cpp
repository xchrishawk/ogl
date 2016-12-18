/**
 * @file	vertex_array.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl/error.hpp"
#include "opengl/exceptions.hpp"
#include "opengl/vertex_array.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

vertex_array::ptr vertex_array::create()
{
  return vertex_array::ptr(new vertex_array());
}

void vertex_array::bind(const vertex_array::const_ptr& vao)
{
  glBindVertexArray(vao->m_handle);
}

void vertex_array::bind_none()
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

void vertex_array::bind_vertex_buffer(GLuint binding_index,
				      const buffer::const_ptr& buffer,
				      GLsizei stride,
				      GLintptr offset)
{
  glVertexArrayVertexBuffer(m_handle,			// vaobj
			    binding_index,		// bindingindex
			    buffer->handle(),		// buffer
			    offset,			// offset
			    stride);			// stride
}

void vertex_array::unbind_vertex_buffer(GLuint binding_index)
{
  glVertexArrayVertexBuffer(m_handle,			// vaobj
			    binding_index,		// bindingindex
			    0,				// buffer
			    0,				// offset
			    0);				// stride
}

void vertex_array::bind_index_buffer(const buffer::const_ptr& buffer)
{
  glVertexArrayElementBuffer(m_handle,			// vaobj
			     buffer->handle());		// buffer
}

void vertex_array::unbind_index_buffer()
{
  glVertexArrayElementBuffer(m_handle,			// vaobj
			     0);			// buffer
}

GLuint vertex_array::new_handle()
{
  GLuint handle = 0;
  glCreateVertexArrays(1, &handle);
  if (handle == 0)
    throw alloc_exception("Failed to create vertex array!");
  return handle;
}
