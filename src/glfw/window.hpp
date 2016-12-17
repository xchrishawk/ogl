/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <GLFW/glfw3.h>

/* -- Types -- */

namespace ogl
{

  /**
   * Wrapper for a GLFW window.
   */
  class window
  {
  public:

    typedef std::shared_ptr<window> ptr;
    typedef std::shared_ptr<const window> const_ptr;

    static window::ptr create();

    ~window();

  private:

    GLFWwindow* m_handle;

    window();
    window(const window&) = delete;
    window& operator =(const window&) = delete;

  };

}
