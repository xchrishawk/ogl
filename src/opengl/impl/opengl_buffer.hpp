/**
 * @file	opengl_buffer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <GL/glew.h>

#include "opengl/buffer.hpp"

/* -- Types -- */

namespace ogl
{
  namespace impl
  {

    /**
     * Base class for concrete implementations of the `ogl::buffer` interface.
     */
    class opengl_buffer : public buffer
    {
    public:

      virtual ~opengl_buffer();

      /** Returns the OpenGL handle for this buffer. */
      GLuint handle() const
      { return m_handle; }

    protected:

      opengl_buffer();

    private:

      const GLuint m_handle;

    };

    /**
     * Class representing an immutable OpenGL buffer.
     *
     * @note
     * The buffer is "immutable" in the sense that its size and location cannot
     * be changed. However, its data can be modified.
     */
    class opengl_immutable_buffer : public opengl_buffer
    {
    public:

      /**
       * Creates a `buffer::ptr` instance wrapping a new OpenGL immutable buffer.
       *
       * @param type
       * The type of buffer to create.
       *
       * @param data
       * The data to load into the buffer, or `nullptr` if the data should be left uninitialized.
       *
       * @param size
       * The size of the buffer, in bytes. Must be greater than or equal to zero.
       *
       * @param flags
       * The flags to use to create the buffer.
       */
      static ogl::buffer::ptr create(ogl::buffer_type type,
				     const void* data,
				     size_t size,
				     ogl::buffer_flags flags);

    private:

      opengl_immutable_buffer(ogl::buffer_type type,
			      const void* data,
			      size_t size,
			      ogl::buffer_flags flags);

    };

  }
}
