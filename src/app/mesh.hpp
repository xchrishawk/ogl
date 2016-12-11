/**
 * mesh.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_MESH_HPP
#define OGL_APP_MESH_HPP

/* -- Includes -- */

#include <memory>
#include <vector>

#include <GL/glew.h>

#include "app/vertex.hpp"
#include "opengl/buffer.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a mesh of vertices.
   */
  class mesh
  {
  public:

    mesh(const std::vector<ogl::vertex>& vertices, const std::vector<GLuint>& elements);

    ogl::immutable_buffer::const_ptr vertex_buffer() const { return m_vertex_buffer; }
    GLsizei vertex_count() const { return m_vertex_count; }
    ogl::immutable_buffer::const_ptr element_buffer() const { return m_element_buffer; }
    GLsizei element_count() const { return m_element_count; }

  private:

    ogl::immutable_buffer::const_ptr m_vertex_buffer;
    GLsizei m_vertex_count;
    ogl::immutable_buffer::const_ptr m_element_buffer;
    GLsizei m_element_count;

  };

}

#endif /* OGL_APP_MESH_HPP */
