/**
 * vertex_array.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_VERTEX_ARRAY_HPP
#define OGL_OPENGL_VERTEX_ARRAY_HPP

/* -- Includes -- */

#include <memory>
#include <GL/glew.h>

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
    static void unbind();

    ~vertex_array();

    void bind() const;

    GLuint handle() const { return m_handle; }

  private:

    GLuint m_handle;

    vertex_array();
    vertex_array(GLuint id);
    vertex_array(const vertex_array& other) = delete;
    vertex_array& operator =(const vertex_array& other) = delete;

  };

}

#endif /* OGL_OPENGL_VERTEX_ARRAY_HPP */
