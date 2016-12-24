/**
 * @file	glfw_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "window/window_manager.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glfw
  {

    /**
     * Interface class wrapping the GLFW library.
     */
    class glfw_interface : public window_manager
    {
    public:

      /** Creates a new GLFW interface instance. */
      static ogl::window_manager::ptr create();

      ~glfw_interface();

    private:

      glfw_interface();

    };

  }
}
