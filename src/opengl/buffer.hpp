/**
 * @file	buffer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include "opengl/api.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract base class for types representing an OpenGL buffer.
   */
  class buffer
  {
  public:

    /** Shared pointer to an `ogl::buffer` object. */
    typedef std::shared_ptr<buffer> ptr;

    /** Shared pointer to a constant `ogl::buffer` object. */
    typedef std::shared_ptr<const buffer> const_ptr;

    virtual ~buffer();

    /** Returns the internal OpenGL handle for this buffer. */
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
   *
   * This buffer is initialized with `glNamedBufferStorage()` as soon as it is
   * created. There is currently no way to update the buffer's data after it has
   * been created.
   */
  class immutable_buffer : public buffer
  {
  public:

    /** Shared pointer to an `ogl::immutable_buffer` object. */
    typedef std::shared_ptr<immutable_buffer> ptr;

    /** Shared pointer to a constant `ogl::immutable_buffer` object. */
    typedef std::shared_ptr<const immutable_buffer> const_ptr;

    /**
     * Creates a new immutable buffer.
     *
     * @param size
     * The size of the buffer, in bytes.
     *
     * @param data
     * A pointer to the data to load into the buffer.
     *
     * @param flags
     * Bitfield of OpenGL flags for this buffer.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new buffer cannot be allocated.
     */
    static ptr create(GLsizei size, const void* data, GLbitfield flags);

  private:

    immutable_buffer(GLsizei size, const void* data, GLbitfield flags);

  };

}
