/**
 * mesh.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <vector>

#include <GL/glew.h>

#include "app/mesh.hpp"
#include "opengl/buffer.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

mesh::mesh(const vector<vertex>& vertices, const vector<mesh_elements>& elements)
  : m_vertices(vertices),
    m_elements(elements)
{
  static const GLbitfield BUFFER_FLAGS = 0;
  m_buffer = immutable_buffer::create(vertices.size() * sizeof(vertex),
				      vertices.data(),
				      BUFFER_FLAGS);
}
