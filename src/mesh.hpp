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

    static ptr create(const vertex* vertices,
		      size_t vertex_count,
		      const GLuint* indices,
		      size_t index_count)
    {
      return ptr(new mesh(vertices, vertex_count, indices, index_count));
    }

    ~mesh();

    GLuint vertex_array() const { return m_vertex_array; }
    size_t vertex_count() const { return m_vertex_count; }
    size_t index_count() const { return m_index_count; }

  private:

    const GLuint m_vertex_array;
    const size_t m_vertex_count;
    const GLuint m_vertex_buffer;
    const size_t m_index_count;
    const GLuint m_index_buffer;

    mesh(const vertex* vertices,
	 size_t vertex_count,
	 const GLuint* indices,
	 size_t index_count);
    mesh(const mesh& other) = delete;
    mesh& operator =(const mesh& other) = delete;

  };

}

#endif /* MESH_HPP */
