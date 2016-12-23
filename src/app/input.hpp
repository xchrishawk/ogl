/**
 * @file	input.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "glfw/glfw.hpp"
#include "glfw/window.hpp"
#include "opengl/api.hpp"

/* -- Types -- */

namespace ogl
{

  // required forward declaration
  class application;

  /**
   * User input interface class.
   */
  class input
  {
  public:

    input(window::const_ptr window);

  private:

    friend class ogl::application;

    const window::const_ptr m_window;

    input(const input& other) = delete;
    input& operator =(const input& other) = delete;

    void key_pressed(int key, int scancode, int action, int mods);

  };

}
