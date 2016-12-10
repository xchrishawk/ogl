/**
 * vertex_array.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_VERTEX_ARRAY_HPP
#define OGL_OPENGL_VERTEX_ARRAY_HPP

/* -- Includes -- */

#include <memory>
#include <GL/glew.h>

#include "opengl/buffer.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL vertex array object (VAO).
   */
  class vertex_array
  {
  public:

    typedef std::shared_ptr<vertex_array> ptr;
    typedef std::shared_ptr<const vertex_array> const_ptr;

    static ptr create();
    static void unactivate();

    ~vertex_array();

    void activate() const;

    void vertex_buffer_format(GLuint binding_index,
			      GLuint attribute_index,
			      GLint size,
			      GLint relative_offset);
    void activate_vertex_buffer(GLuint binding_index,
				immutable_buffer::const_ptr buffer,
				GLsizei stride,
				GLintptr offset = 0);
    void unactivate_vertex_buffer(GLuint binding_index);

    GLuint handle() const { return m_handle; }

  private:

    GLuint m_handle;

    vertex_array();
    vertex_array(const vertex_array& other) = delete;
    vertex_array& operator =(const vertex_array& other) = delete;

    static GLuint new_handle();

  };

}

#endif /* OGL_OPENGL_VERTEX_ARRAY_HPP */
