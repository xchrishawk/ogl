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

    mesh(const std::vector<vertex>& vertices);

    ogl::immutable_buffer::const_ptr buffer() const { return m_buffer; }
    GLsizei count() const { return m_count; }

  private:

    ogl::immutable_buffer::const_ptr m_buffer;
    GLsizei m_count;

  };

  /**
   * Class generating example meshes for prototyping.
   */
  class example_meshes
  {
  public:

    static mesh rgb_triangle();
    static mesh cmy_triangle();

  private:

    // non-instantiable class
    example_meshes() = delete;
    example_meshes(const example_meshes&) = delete;
    example_meshes& operator =(const example_meshes&) = delete;

  };

}

#endif /* OGL_APP_MESH_HPP */
