/**
 * @file	opengl_shader.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>

#include "opengl/api.hpp"
#include "opengl/shader.hpp"

/* -- Types -- */

namespace ogl
{
  namespace impl
  {

    /**
     * Concrete implementation of the `ogl::shader` interface.
     */
    class opengl_shader final : public shader
    {
    public:

      /**
       * Creates a shared pointer to a new `opengl_shader` instance.
       *
       * @param type
       * The type of shader to create.
       *
       * @exception ogl::opengl_exception
       * Thrown if the shader cannot be created for any reason.
       */
      static ogl::shader::ptr create(GLenum type);

      ~opengl_shader();

      /** Returns the OpenGL handle for this shader. */
      GLuint handle() const
      { return m_handle; }

      /* -- `shader` Interface Implementation -- */

      virtual void set_source(const std::string& source);
      virtual void compile();
      virtual bool is_compiled() const;
      virtual std::string info_log() const;

    private:

      const GLuint m_handle;

      opengl_shader(GLenum type);

    };

  }
}
