/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "app/input.hpp"
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

    static application* s_instance;

    glfw m_glfw;
    window::ptr m_window;
    glew m_glew;
    input m_input;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

    void handle_input(double abs_t, double delta_t);
    void handle_state(double abs_t, double delta_t);
    void handle_render(double abs_t, double delta_t);

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  };

}
