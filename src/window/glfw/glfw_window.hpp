/**
 * @file	glfw_window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <GLFW/glfw3.h>
#include "window/window.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glfw
  {

    /**
     * Class representing a GLFW window.
     */
    class glfw_window : public window
    {
    public:

      /** Creates a shared pointer to a new `glfw_window` instance. */
      static ogl::window::ptr create();

      ~glfw_window();

    private:

      GLFWwindow* m_handle;

      glfw_window();

    };

  }
}
