/**
 * mesh.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <memory>
#include <vector>

#include "app/mesh.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

mesh::mesh(const vector<vertex>& vertices)
{
  m_count = vertices.size();
  m_buffer = immutable_buffer::create(m_count * sizeof(vertex), vertices.data(), 0);
}
