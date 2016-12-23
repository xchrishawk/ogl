/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

#include <vector>

/* -- Types -- */

namespace ogl
{

  /**
   * Enumeration of input keys.
   */
  enum input_key
  {
    INPUT_KEY_INVALID,

    INPUT_KEY_APPLICATION_EXIT,
    INPUT_KEY_CAMERA_RESET,

    INPUT_KEY_COUNT,
    INPUT_KEY_FIRST_VALID = INPUT_KEY_APPLICATION_EXIT,
    INPUT_KEY_LAST_VALID = INPUT_KEY_CAMERA_RESET,
  };

  /**
   * Abstract interface for types observing input keys.
   */
  class input_key_observer
  {
  public:

    /** The specified input key was pressed by the user. */
    virtual void input_key_pressed(input_key input) = 0;

  };

  /**
   * Class responsible for handling inputs to the application.
   */
  class input_manager
  {
  public:

    input_manager();

    /**
     * Handles the specified keypress.
     *
     * @note
     * This should only be called by the `application` class to handle key press
     * events from the GLFW window.
     */
    void handle_key(int key, int scancode, int action, int mods);

    /** Returns `true` if the specified key is in an active state. */
    bool input_key_state(input_key input) const;

    /** Adds an input key observer. */
    void add_input_key_observer(input_key_observer* observer);

    /** Removes an input key observer. */
    void remove_input_key_observer(input_key_observer* observer);

  private:

    bool m_input_keys[INPUT_KEY_COUNT];
    std::vector<input_key_observer*> m_input_key_observers;

    void handle_key_press(int key, int mods);
    void handle_key_release(int key, int mods);
    void notify_input_key(input_key key);

    static input_key input_key_for_key(int key, int mods);
    static bool should_notify_input_key(input_key key);
    static bool input_key_valid(input_key key);

  };

}
