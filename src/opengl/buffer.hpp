/**
 * buffer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_BUFFER_HPP
#define OGL_OPENGL_BUFFER_HPP

/* -- Includes -- */

#include <memory>
#include <GL/glew.h>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract base class for classes managing an OpenGL buffer.
   */
  class buffer
  {
  public:

    virtual ~buffer();

    GLuint id() const { return m_id; }
    operator GLuint() { return m_id; }

  protected:

    buffer();

  private:

    GLuint m_id;

    buffer(const buffer& other);
    buffer& operator =(const buffer& other);

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
