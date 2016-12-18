/**
 * @file	mesh.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <vector>

#include "opengl/api.hpp"
#include "opengl/buffer.hpp"
#include "scene/vertex.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a renderable mesh in a scene.
   */
  class mesh
  {

  public:

    /**
     * Creates a new `ogl::mesh` object.
     *
     * @param type
     * The type of mesh to draw (`GL_TRIANGLES`, `GL_TRIANGLE_FAN`, etc).
     *
     * @param vertices
     * A `std::vector` of vertices included in the mesh.
     *
     * @param indices
     * A `std::vector` of draw indices to use when drawing the mesh.
     *
     * @exception ogl::alloc_exception
     * Thrown if a backing buffer cannot be created.
     */
    mesh(GLenum type,
	 const std::vector<vertex>& vertices,
	 const std::vector<GLuint>& indices);

    /** The type of mesh to draw (e.g., `GL_TRIANGLES`, `GL_TRIANGLE_FAN`, etc). */
    GLenum type() const { return m_type; }

    /** The number of vertices in this mesh. */
    GLsizei vertex_count() const { return m_vertex_count; }

    /** The number of draw indices in this mesh. */
    GLsizei index_count() const { return m_index_count; }

  private:

    const GLenum m_type;
    const GLsizei m_vertex_count;
    const buffer::const_ptr m_vertex_buffer;
    const GLsizei m_index_count;
    const buffer::const_ptr m_index_buffer;

  };

}
