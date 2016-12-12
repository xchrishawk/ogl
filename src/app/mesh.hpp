/**
 * mesh.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_MESH_HPP
#define OGL_APP_MESH_HPP

/* -- Includes -- */

#include <vector>
#include <GL/glew.h>

#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "opengl/texture.hpp"

/* -- Types -- */

namespace ogl
{

  class mesh_elements;

  /**
   * Class representing a drawable vertex mesh.
   */
  class mesh
  {
  public:

    mesh(const std::vector<ogl::vertex>& vertices,
	 const std::vector<ogl::mesh_elements>& elements);

    std::vector<ogl::vertex> vertices() const { return m_vertices; }
    std::vector<ogl::mesh_elements> elements() const { return m_elements; }
    ogl::immutable_buffer::const_ptr buffer() const { return m_buffer; }

  private:

    std::vector<ogl::vertex> m_vertices;
    std::vector<ogl::mesh_elements> m_elements;
    ogl::immutable_buffer::const_ptr m_buffer;

  };

  /**
   * Class representing a set of drawable elements in a mesh.
   */
  class mesh_elements
  {
  public:

    mesh_elements(GLenum mode,
		  const std::vector<GLuint>& indices,
		  const ogl::texture2d::const_ptr& texture = ogl::texture2d::const_ptr(nullptr))
      : m_mode(mode),
	m_indices(indices),
	m_texture(texture)
    { }

    GLenum mode() const { return m_mode; }
    GLsizei count() const { return static_cast<GLsizei>(m_indices.size()); }
    GLenum type() const { return GL_UNSIGNED_INT; }
    const void* indices() const { return m_indices.data(); }
    ogl::texture2d::const_ptr texture() const { return m_texture; }

  private:

    GLenum m_mode;
    std::vector<GLuint> m_indices;
    ogl::texture2d::const_ptr m_texture;

  };

}

#endif /* OGL_APP_MESH_HPP */
