/**
 * @file	opengl_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

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

      /** Creates a new OpenGL interface instance. */
      static ogl::opengl::ptr create();

      ~opengl_interface();

      /* -- `opengl` Interface Implentation -- */

      // factory methods
      virtual ogl::shader::ptr create_shader(ogl::shader_type type) const;

      // platform information
      virtual std::string version() const;
      virtual std::string glsl_version() const;
      virtual std::string vendor() const;
      virtual std::string renderer() const;

      // error handling
      virtual ogl::opengl_error last_error() const;
      virtual std::string error_string(ogl::opengl_error error) const;

    private:

      static opengl_interface* s_instance;

      opengl_interface();

    };

  }
}
