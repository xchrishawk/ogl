/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "opengl/opengl.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"
#include "window/window_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information needed to construct an `application` instance.
   */
  struct application_args
  {
    ogl::window_manager::ptr window_manager;	/**< The window manager interface. */
    ogl::window::ptr window;			/**< The main application window. */
    ogl::opengl::ptr opengl;			/**< The OpenGL interface. */
    ogl::input_manager::ptr input_manager;	/**< The input manager. */
    ogl::state_manager::ptr state_manager;	/**< The state manager. */
    double target_state_delta_t;		/**< Time between state loops. */
    double target_render_delta_t;		/**< Time between render loops. */
  };

  /**
   * Main class for the OGL application.
   */
  class application : public input_observer
  {
  public:

    /**
     * Creates a new application instance.
     *
     * @note
     * Only a single instance of this type may be created at a single time. If
     * multiple instances are created, the program will fail.
     *
     * @param args
     * Struct containing arguments used to create the instance.
     */
    application(const application_args& args);

    ~application();

    /** Runs the main loop for the application. */
    void main();

    /* -- `input_observer` Interface Implementation -- */

    virtual void command_activated(ogl::input_command key);
    virtual void command_deactivated(ogl::input_command key);

  private:

    static application* s_instance;

    const ogl::window_manager::ptr m_window_manager;
    const ogl::window::ptr m_window;
    const ogl::opengl::ptr m_opengl;
    const ogl::input_manager::ptr m_input_manager;
    const ogl::state_manager::ptr m_state_manager;
    const double m_target_state_delta_t;
    const double m_target_render_delta_t;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

    void run_input();
    void run_state(double abs_t, double delta_t);
    void run_render(double abs_t, double delta_t);

  };

}
