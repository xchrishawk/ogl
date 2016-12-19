/**
 * @file	mesh.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include <vector>

#include "opengl/api.hpp"
#include "opengl/buffer.hpp"
#include "scene/mesh.hpp"
#include "scene/vertex.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

mesh::mesh(GLenum type,
	   const std::vector<vertex>& vertices,
	   const std::vector<GLuint>& indices)
  : m_type(type),
    m_vertex_count(vertices.size()),
    m_vertex_buffer(immutable_buffer::create(vertices, 0)),
    m_index_count(indices.size()),
    m_index_buffer(immutable_buffer::create(indices, 0))
{
}

mesh::mesh(const mesh& other)
  : m_type(other.m_type),
    m_vertex_count(other.m_vertex_count),
    m_vertex_buffer(other.m_vertex_buffer),
    m_index_count(other.m_index_count),
    m_index_buffer(other.m_index_buffer)
{
}

mesh& mesh::operator =(const mesh& other)
{
  m_type = other.m_type;
  m_vertex_count = other.m_vertex_count;
  m_vertex_buffer = other.m_vertex_buffer;
  m_index_count = other.m_index_count;
  m_index_buffer = other.m_vertex_buffer;

  return *this;
}
