/**
 * @file	opengl_shader.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include "opengl/shader.hpp"

/* -- Types -- */

namespace ogl
{
  namespace impl
  {

    /**
     * Concrete implementation of the `ogl::shader` interface.
     */
    class opengl_shader : public shader
    {
    public:

      /** Creates a shared pointer to a new `opengl_shader` instance. */
      static ogl::shader::ptr create(ogl::shader_type type);

      ~opengl_shader();

    private:

      opengl_shader(ogl::shader_type type);

    };

  }
}
