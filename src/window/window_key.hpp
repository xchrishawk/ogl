/**
 * @file	window_key.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  // Forward declaration
  class window;

  enum class window_key : int
  {

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

}
