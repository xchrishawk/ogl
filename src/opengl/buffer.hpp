/**
 * @file	buffer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <vector>

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

    /** Maps the entire buffer to memory. */
    void* map(GLenum access);

    /** Maps a portion of the buffer to memory. */
    void* map_range(GLintptr offset, GLsizei lenth, GLbitfield access);

    /** Updates a portion of the buffer's data. */
    void sub_data(GLintptr offset, GLsizei size, const void* data);

    /** Returns `true` if this is an immutable buffer. */
    bool is_immutable() const;

    /** Returns `true` if this buffer is currently mapped. */
    bool is_mapped() const;

    /** Returns the number of bytes currently mapped from this buffer. */
    GLint64 map_length() const;

    /** Returns the offset of the region currently mapped from this buffer. */
    GLint64 map_offset() const;

    /** Returns the current size of the buffer, in bytes. */
    GLint size() const;

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
   * created. The buffer is "immutable" in the sense that its location and size
   * cannot be changed. However, its data contents may be changed.
   */
  class immutable_buffer : public buffer
  {
  public:

    /** Shared pointer to an `ogl::immutable_buffer` object. */
    typedef std::shared_ptr<immutable_buffer> ptr;

    /** Shared pointer to a constant `ogl::immutable_buffer` object. */
    typedef std::shared_ptr<const immutable_buffer> const_ptr;

    /**
     * Creates a new immutable buffer from an existing data buffer.
     *
     * @param size
     * The size of the buffer, in bytes.
     *
     * @param data
     * A pointer to the data to load into the buffer, or `NULL` to leave the
     * initial contents of the buffer unspecified.
     *
     * @param flags
     * Bitfield of OpenGL flags for this buffer.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new buffer cannot be allocated.
     */
    static ptr create(GLsizei size, const void* data, GLbitfield flags);

    /**
     * Creates a new immutable buffer from a `std::vector`.
     *
     * @param elements
     * A vector of elements to include in the buffer.
     *
     * @param flags
     * Bitfield of OpenGL flags for this buffer.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new buffer cannot be allocated.
     */
    template<typename T>
    static ptr create(std::vector<T> elements, GLbitfield flags)
    {
      return create(elements.size() * sizeof(T),
		    elements.data(),
		    flags);
    }

  private:

    immutable_buffer(GLsizei size, const void* data, GLbitfield flags);

  };

}
