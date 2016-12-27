/**
 * @file	buffer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Constants -- */

namespace ogl
{

  /**
   * Enumeration of OpenGL buffer types.
   */
  enum class buffer_type : int
  {
    array_buffer,					/**< Equivalent to GL_ARRAY_BUFFER. */
    atomic_counter_buffer,				/**< Equivalent to GL_ATOMIC_COUNTER_BUFFER. */
    copy_read_buffer,					/**< Equivalent to GL_COPY_READ_BUFFER. */
    copy_write_buffer,					/**< Equivalent to GL_COPY_WRITE_BUFFER. */
    dispatch_indirect_buffer,				/**< Equivalent to GL_DISPATCH_INDIRECT_BUFFER. */
    draw_indirect_buffer,				/**< Equivalent to GL_DRAW_INDIRECT_BUFFER. */
    element_array_buffer,				/**< Equivalent to GL_ELEMENT_ARRAY_BUFFER. */
    pixel_pack_buffer,					/**< Equivalent to GL_PIXEL_PACK_BUFFER. */
    pixel_unpack_buffer,				/**< Equivalent to GL_PIXEL_UNPACK_BUFFER. */
    query_buffer,					/**< Equivalent to GL_QUERY_BUFFER. */
    shader_storage_buffer,				/**< Equivalent to GL_SHADER_STORAGE_BUFFER. */
    texture_buffer,					/**< Equivalent to GL_TEXTURE_BUFFER. */
    transform_feedback_buffer,        			/**< Equivalent to GL_TRANSFORM_FEEDBACK_BUFFER. */
    uniform_buffer,		        		/**< Equivalent to GL_UNIFORM_BUFFER. */
  };

  /**
   * Enumeration of OpenGL buffer usage flags.
   */
  enum class buffer_usage : int
  {
    stream_draw,					/**< Equivalent to GL_STREAM_DRAW. */
    stream_read,					/**< Equivalent to GL_STREAM_READ. */
    stream_copy,					/**< Equivalent to GL_STREAM_COPY. */
    static_draw,					/**< Equivalent to GL_STATIC_DRAW. */
    static_read,					/**< Equivalent to GL_STATIC_READ. */
    static_copy,					/**< Equivalent to GL_STATIC_COPY. */
    dynamic_draw,					/**< Equivalent to GL_DYNAMIC_DRAW. */
    dynamic_read,					/**< Equivalent to GL_DYNAMIC_READ. */
    dynamic_copy,					/**< Equivalent to GL_DYNAMIC_COPY. */
  };

  /**
   * Enumeration of OpenGL buffer flags.
   */
  enum buffer_flags
  {
    BUFFER_FLAGS_NONE			= 0x0,		/**< No flags. */
    BUFFER_FLAGS_DYNAMIC_STORAGE	= 0x1,		/**< Equivalent to GL_DYNAMIC_STORAGE_BIT. */
    BUFFER_FLAGS_MAP_READ		= 0x2,		/**< Equivalent to GL_MAP_READ_BIT. */
    BUFFER_FLAGS_MAP_WRITE		= 0x4,		/**< Equivalent to GL_MAP_WRITE_BIT. */
    BUFFER_FLAGS_MAP_PERSISTENT		= 0x8,		/**< Equivalent to GL_MAP_PERSISTENT_BIT. */
    BUFFER_FLAGS_MAP_COHERENT		= 0x10,		/**< Equivalent to GL_MAP_COHERENT_BIT. */
    BUFFER_FLAGS_CLIENT_STORAGE		= 0x20,		/**< Equivalent to GL_CLIENT_STORAGE_BIT. */
  };

}

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing an OpenGL buffer.
   */
  class buffer
  {
  public:

    /** Shared pointer to a `buffer` instance. */
    typedef std::shared_ptr<buffer> ptr;

    /** Shared pointer to a `const buffer` instance. */
    typedef std::shared_ptr<const buffer> const_ptr;

    virtual ~buffer() { }

  protected:

    buffer() { }

  private:

    buffer(const buffer&) = delete;
    buffer& operator =(const buffer&) = delete;

  };

}
