/**
 * @file	glfw.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
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
