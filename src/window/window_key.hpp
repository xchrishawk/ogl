/**
 * @file	window_key.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <sstream>
#include "util/debug.hpp"

/* -- Types -- */

namespace ogl
{

  // Forward declaration
  class window;

  /**
   * Enumeration of key press events which may be sent from a window.
   */
  enum class window_key : int
  {
    invalid,
  };

  /**
   * Abstract interface for classes which can observe key events from a window.
   */
  class window_key_observer
  {
  public:

    /**
     * Notifies the observer that a key was pressed on this window.
     *
     * @param window
     * The window on which the key was pressed.
     *
     * @param key
     * The key which was pressed.
     */
    virtual void window_key_pressed(const ogl::window* window, window_key key) = 0;

  };

#if defined(OGL_DEBUG)

  /**
   * Simple test implementation of `window_key_observer`.
   */
  class window_key_debugger final : public window_key_observer
  {
  public:

    /** Prints a debug message when a key is pressed. */
    virtual void window_key_pressed(const ogl::window* window, window_key key)
    {
      std::ostringstream message;
      message << "Key received from " << window << ": " << static_cast<int>(key);
      ogl_dbg_status(message.str());
    }

  };

#endif /* defined(OGL_DEBUG) */

}
