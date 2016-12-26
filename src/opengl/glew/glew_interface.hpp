/**
 * @file	glew_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glew
  {

    /**
     * Class representing an OpenGL interface using GLEW.
     */
    class glew_interface final : public opengl
    {
    public:

      /** Creates a new GLEW/OpenGL interface instance. */
      static ogl::opengl::ptr create();

      ~glew_interface();

    private:

      static glew_interface* s_instance;

      glew_interface();

    };

  }
}
