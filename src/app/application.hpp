/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "glew/glew.hpp"
#include "glfw/glfw.hpp"
#include "glfw/window.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Main application class.
   */
  class application
  {
  public:

    application();
    ~application();

    /** Runs the application's main loop. */
    void main();

  private:

    glfw m_glfw;
    window::ptr m_window;
    glew m_glew;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}
