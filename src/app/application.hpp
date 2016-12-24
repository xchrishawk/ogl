/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "opengl/opengl.hpp"
#include "window/window.hpp"
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
  };

  /**
   * Main class for the OGL application.
   */
  class application
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

  private:

    static application* s_instance;

    const ogl::window_manager::ptr m_window_manager;
    const ogl::window::ptr m_window;
    const ogl::opengl::ptr m_opengl;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}
