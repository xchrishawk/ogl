/**
 * mesh.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <memory>
#include <vector>

#include "app/mesh.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

mesh::mesh(const vector<vertex>& vertices, const vector<GLuint>& elements)
{
  m_vertex_count = vertices.size();
  m_vertex_buffer = immutable_buffer::create(m_vertex_count * sizeof(vertex), vertices.data(), 0);
  m_element_count = elements.size();
  m_element_buffer = immutable_buffer::create(m_element_count * sizeof(GLuint), elements.data(), 0);
}
