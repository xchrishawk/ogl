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
#include "shader_source.hpp"
#include "util.hpp"
#include "vertex_array.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  GLuint init_buffer();
}

/* -- Procedures -- */

mesh::mesh(const vertex* vertices,
	   size_t vertex_count,
	   const GLuint* indices,
	   size_t index_count)
  : m_vertex_array(vertex_array::create()),
    m_vertex_count(vertex_count),
    m_vertex_buffer(init_buffer()),
    m_index_count(index_count),
    m_index_buffer(init_buffer())
{
  // initialize buffer storage
  glNamedBufferStorage(m_vertex_buffer,
		       m_vertex_count * sizeof(vertex),
		       vertices,
		       GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
  glNamedBufferStorage(m_index_buffer,
		       m_index_count * sizeof(GLuint),
		       indices,
		       GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

  // create binding to buffer
  static const GLuint BINDING_INDEX = 0;
  glVertexArrayVertexBuffer(m_vertex_array->id(),		// vaobj
			    BINDING_INDEX,			// bindingindex
			    m_vertex_buffer,			// buffer
			    0,					// offset
			    sizeof(vertex));			// stride

  // set position format
  glVertexArrayAttribFormat(m_vertex_array->id(),		// vaobj
			    POSITION_ATTRIBUTE_LOCATION,	// attribindex
			    vertex::position_count,		// size
			    GL_FLOAT,				// type
			    GL_FALSE,				// normalized
			    vertex::position_offset);		// relativeoffset

  // bind position attribute
  glVertexArrayAttribBinding(m_vertex_array->id(),		// vaobj
			     POSITION_ATTRIBUTE_LOCATION,	// attribindex
			     BINDING_INDEX);			// bindingindex

  // enable position attribute array
  glEnableVertexArrayAttrib(m_vertex_array->id(),		// vaobj
			    POSITION_ATTRIBUTE_LOCATION);	// attribindex

  // set color format
  glVertexArrayAttribFormat(m_vertex_array->id(),		// vaobj
			    COLOR_ATTRIBUTE_LOCATION,		// attribindex
			    vertex::color_count,		// size
			    GL_FLOAT,				// type
			    GL_FALSE,				// normalized
			    vertex::color_offset);		// relativeoffset

  // bind color attribute
  glVertexArrayAttribBinding(m_vertex_array->id(),		// vaobj
			     COLOR_ATTRIBUTE_LOCATION,		// attribindex
			     BINDING_INDEX);			// bindingindex

  // enable color attribute array
  glEnableVertexArrayAttrib(m_vertex_array->id(),		// vaobj
			    COLOR_ATTRIBUTE_LOCATION);		// attribindex

  // set up index buffer
  glVertexArrayElementBuffer(m_vertex_array->id(),		// vaobj
			     m_index_buffer);			// buffer
}

mesh::~mesh()
{
  glDeleteBuffers(1, &m_vertex_buffer);
  glDeleteBuffers(1, &m_index_buffer);
}

namespace
{

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
