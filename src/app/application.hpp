/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "app/input_manager.hpp"
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

    virtual void input_key_activated(ogl::input_key key);
    virtual void input_key_deactivated(ogl::input_key key);

  private:

    static application* s_instance;

    const ogl::window_manager::ptr m_window_manager;
    const ogl::window::ptr m_window;
    const ogl::opengl::ptr m_opengl;
    const ogl::input_manager::ptr m_input_manager;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}
