/**
 * @file	opengl_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "opengl/api.hpp"
#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{
  namespace impl
  {

    /**
     * Class representing an OpenGL interface using GLEW.
     */
    class opengl_interface final : public opengl
    {
    public:

      /**
       * Creates a new OpenGL interface instance.
       *
       * @exception ogl::opengl_exception
       * Thrown if the OpenGL interface cannot be initialized for any reason.
       */
      static ogl::opengl::ptr create();

      ~opengl_interface();

      /* -- `opengl` Interface Implentation -- */

      // factory methods
      virtual ogl::shader::ptr create_shader(GLenum type) const;
      virtual ogl::program::ptr create_program() const;
      virtual ogl::buffer::ptr create_immutable_buffer(GLenum type,
						       const void* data,
						       size_t size,
						       GLbitfield flags) const;

      // platform information
      virtual std::string version() const;
      virtual std::string glsl_version() const;
      virtual std::string vendor() const;
      virtual std::string renderer() const;

      // error handling
      virtual GLenum last_error() const;
      virtual std::string error_string(GLenum error) const;

    private:

      static opengl_interface* s_instance;

      opengl_interface();

    };

  }
}
