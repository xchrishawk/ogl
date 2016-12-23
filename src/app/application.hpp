/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "app/renderer.hpp"
#include "app/state_manager.hpp"
#include "glfw/glfw.hpp"
#include "glfw/window.hpp"
#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Main application class.
   */
  class application : public ogl::input_key_observer
  {
  public:

    application();
    ~application();

    /** Runs the application's main loop. */
    void main();

    /** Method for `input_key_observer`. */
    void input_key_pressed(input_key input);

  private:

    static application* s_instance;

    ogl::glfw m_glfw;
    ogl::window::ptr m_window;
    ogl::opengl m_opengl;
    ogl::input_manager m_input_manager;
    ogl::state_manager m_state_manager;
    ogl::renderer m_renderer;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

    void handle_input();
    void handle_state(double abs_t, double delta_t);
    void handle_render(double abs_t, double delta_t);

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  };

}
