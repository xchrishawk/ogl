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
    escape,
    digit_0,
    digit_1,
    digit_2,
    digit_3,
    digit_4,
    digit_5,
    digit_6,
    digit_7,
    digit_8,
    digit_9,
  };

  /**
   * Enumeration of key actions which may be sent from a window.
   */
  enum class window_key_action : int
  {
    invalid,		/**< Invalid action type. */
    press,		/**< The key was pressed. */
    release,		/**< The key was release. */
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
    virtual void window_key_pressed(const ogl::window* window,
				    ogl::window_key key,
				    ogl::window_key_action action) = 0;

  };

#if defined(OGL_DEBUG)

  /**
   * Simple test implementation of `window_key_observer`.
   */
  class window_key_debugger final : public window_key_observer
  {
  public:

    /** Prints a debug message when a key is pressed. */
    virtual void window_key_pressed(const ogl::window* window,
				    ogl::window_key key,
				    ogl::window_key_action action)
    {
      std::ostringstream message;
      message << "Key received from " << window
	      << ": " << static_cast<int>(key)
	      << " (action " << static_cast<int>(action) << ")";
      ogl_dbg_status(message.str());
    }

  };

#endif /* defined(OGL_DEBUG) */

}
