/**
 * @file	input.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

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

    input();

  private:

    friend class ogl::application;

    input(const input& other) = delete;
    input& operator =(const input& other) = delete;

    void key_pressed(int key, int scancode, int action, int mods);

  };

}
