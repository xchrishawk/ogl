/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Types -- */

namespace app
{

  /**
   * Abstract interface for types representing a window manager library.
   */
  class window_manager
  {
  public:

    virtual ~window_manager() = default;

    /** Returns the current elapsed time, in seconds. */
    virtual double time() const = 0;

    /** Polls the window manager for events. */
    virtual void poll_events() const = 0;

  protected:

    window_manager() = default;

  private:

    window_manager(const app::window_manager&) = delete;
    app::window_manager& operator =(const app::window_manager&) = delete;

  };

}
