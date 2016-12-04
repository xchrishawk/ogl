/**
 * mesh.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "mesh.hpp"
#include "opengl.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  GLuint init_vertex_array();
  GLuint init_buffer();
}

/* -- Procedures -- */

mesh::ptr mesh::create(const vertex* vertices, size_t count)
{
  return mesh::ptr(new mesh(vertices, count));
}

mesh::mesh(const vertex* vertices, size_t count)
  : m_vertex_count(count),
    m_vertex_array(init_vertex_array()),
    m_buffer(init_buffer())
{
  // initialize buffer storage
  glNamedBufferStorage(m_buffer,
		       m_vertex_count * sizeof(vertex),
		       vertices,
		       GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

  // create binding to buffer
  static const GLuint BINDING_INDEX = 0;
  glVertexArrayVertexBuffer(m_vertex_array,		// vaobj
			    BINDING_INDEX,		// bindingindex
			    m_buffer,			// buffer
			    0,				// offset
			    sizeof(vertex));		// stride

  // set position format
  glVertexArrayAttribFormat(m_vertex_array,		// vaobj
			    0,				// attribindex
			    vertex::position_count,	// size
			    GL_FLOAT,			// type
			    GL_FALSE,			// normalized
			    vertex::position_offset);	// relativeoffset

  // bind position attribute
  glVertexArrayAttribBinding(m_vertex_array,		// vaobj
			     0,				// attribindex
			     BINDING_INDEX);		// bindingindex

  // enable position attribute array
  glEnableVertexArrayAttrib(m_vertex_array,		// vaobj
			    0);				// attribindex

  // set color format
  glVertexArrayAttribFormat(m_vertex_array,		// vaobj
			    1,				// attribindex
			    vertex::color_count,	// size
			    GL_FLOAT,			// type
			    GL_FALSE,			// normalized
			    vertex::color_offset);	// relativeoffset

  // bind color attribute
  glVertexArrayAttribBinding(m_vertex_array,		// vaobj
			     1,				// attribindex
			     BINDING_INDEX);		// bindingindex

  // enable color attribute array
  glEnableVertexArrayAttrib(m_vertex_array,		// vaobj
			    1);				// attribindex
}

mesh::~mesh()
{
  glDeleteBuffers(1, &m_buffer);
  glDeleteVertexArrays(1, &m_vertex_array);
}

namespace
{

  GLuint init_vertex_array()
  {
    GLuint vao = 0;

    glCreateVertexArrays(1, &vao);
    if (vao == 0)
    {
      GLenum error = opengl_last_error();
      ostringstream message;
      message << "Failed to create vertex array. " << opengl_error_string(error);
      throw runtime_error(message.str());
    }

    return vao;
  }

  GLuint init_buffer()
  {
    GLuint buffer = 0;

    glCreateBuffers(1, &buffer);
    if (buffer == 0)
    {
      GLenum error = opengl_last_error();
      ostringstream message;
      message << "Failed to create buffer. " << opengl_error_string(error);
      throw runtime_error(message.str());
    }

    return buffer;
  }

}