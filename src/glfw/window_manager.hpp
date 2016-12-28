/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include "app/window_manager.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Concrete implementation of `ogl::window_manager` using the GLFW library.
   */
  class window_manager final
    : public ogl::window_manager
  {
  public:

  private:

    window_manager();
    window_manager(const glfw::window_manager&) = delete;
    glfw::window_manager& operator =(const glfw::window_manager&) = delete;

  };

}
