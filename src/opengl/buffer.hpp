/**
 * buffer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_BUFFER_HPP
#define OGL_OPENGL_BUFFER_HPP

/* -- Includes -- */

#include <memory>
#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL buffer.
   */
  class buffer
  {
  public:

    virtual ~buffer();

    GLuint handle() const { return m_handle; }

  protected:

    buffer();

  private:

    const GLuint m_handle;

    buffer(const buffer&) = delete;
    buffer& operator =(const buffer&) = delete;

    static GLuint new_handle();

  };

  /**
   * Class representing an immutable OpenGL buffer.
   */
  class immutable_buffer : public buffer
  {
  public:

    typedef std::shared_ptr<immutable_buffer> ptr;
    typedef std::shared_ptr<const immutable_buffer> const_ptr;

    static ptr create(GLsizei size, const void* data, GLbitfield flags);

  private:

    immutable_buffer(GLsizei size, const void* data, GLbitfield flags);

  };

}

#endif /* OGL_OPENGL_BUFFER_HPP */
