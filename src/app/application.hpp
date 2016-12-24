/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include "window/window_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Main class for the OGL application.
   */
  class application
  {
  public:

    application(const window_manager::ptr& window_manager);
    ~application();

    /** Runs the main loop for the application. */
    void main();

  private:

    static application* s_instance;

    const window_manager::ptr m_window_manager;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}
