/**
 * vertex_array.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

/* -- Includes -- */

#include <memory>
#include "opengl.hpp"

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

    GLuint id() const { return m_id; }

  private:

    GLuint m_id;

    vertex_array();
    vertex_array(GLuint id);
    vertex_array(const vertex_array& other) = delete;
    vertex_array& operator =(const vertex_array& other) = delete;

  };

}

#endif /* VERTEX_ARRAY_HPP */
