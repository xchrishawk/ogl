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

  }
}
