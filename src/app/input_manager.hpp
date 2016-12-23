/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

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

  private:

    bool m_input_keys[INPUT_KEY_COUNT];

    void handle_key_press(int key, int mods);
    void handle_key_release(int key, int mods);
    input_key input_key_for_key(int key, int mods);
    bool should_notify_input_key(input_key key);
    void notify_input_key(input_key key);
    bool input_key_valid(input_key key);

  };

}
