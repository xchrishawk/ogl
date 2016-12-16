/**
 * glfw.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * RAII wrapper for the GLFW library.
   */
  class glfw
  {
  public:

    glfw();
    ~glfw();

  private:

    glfw(const glfw&) = delete;
    glfw& operator =(const glfw&) = delete;

  };

}
