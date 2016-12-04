/**
 * mesh.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef MESH_HPP
#define MESH_HPP

/* -- Includes -- */

#include <memory>
#include <vector>

#include "opengl.hpp"
#include "vertex.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a vertex mesh for rendering.
   */
  class mesh
  {
  public:

    typedef std::shared_ptr<mesh> ptr;
    typedef std::shared_ptr<const mesh> const_ptr;

    static ptr create(const vertex* vertices, size_t count);
    ~mesh();

    size_t vertex_count() const { return m_vertex_count; }
    GLuint vertex_array() const { return m_vertex_array; }
    GLuint buffer() const { return m_buffer; }

  private:

    const size_t m_vertex_count;
    const GLuint m_vertex_array;
    const GLuint m_buffer;

    mesh(const vertex* vertices, size_t count);
    mesh(const mesh& other) = delete;
    mesh& operator =(const mesh& other) = delete;

  };

}

#endif /* MESH_HPP */
