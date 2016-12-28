/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

#pragma once

/* -- Types -- */

namespace app
{

  /**
   * Abstract interface for types representing a window.
   */
  class window
  {
  public:

    virtual ~window() = default;

    /** Returns `true` if this window is the active OpenGL context. */
    virtual bool is_current_context() const = 0;

    /** Sets this window as the active OpenGL context. */
    virtual void make_current_context() = 0;

    /** Swaps the front and back buffers for this window. */
    virtual void swap_buffers() = 0;

    /** Returns `true` if this window's "should close" flag is set. */
    virtual bool should_close() const = 0;

    /** Sets the window's "should close" flag. */
    virtual void set_should_close(bool should_close) = 0;

  protected:

    window() = default;

  private:

    window(const app::window&) = delete;
    app::window& operator =(const app::window&) = delete;

  };

}
