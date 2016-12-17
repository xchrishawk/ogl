/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "app/input.hpp"
#include "app/renderer.hpp"
#include "app/state.hpp"

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

    input m_input;
    state m_state;
    renderer m_renderer;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

    void handle_input(double abs_t, double delta_t);
    void handle_state(double abs_t, double delta_t);
    void handle_render(double abs_t, double delta_t);

  };

}
