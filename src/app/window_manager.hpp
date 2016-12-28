/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing a window manager library.
   */
  class window_manager
  {
  public:

    virtual ~window_manager() { }

    /** Returns the current elapsed time, in seconds. */
    virtual double time() const = 0;

    /** Polls the window manager for events. */
    virtual void poll_events() const = 0;

  protected:

    window_manager() { }

  private:

    window_manager(const ogl::window_manager&) = delete;
    ogl::window_manager& operator =(const ogl::window_manager&) = delete;

  };

}
