/**
 * key_input.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef KEY_INPUT_HPP
#define KEY_INPUT_HPP

/* -- Includes -- */

#include "opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Enumeration of available key presses.
   */
  enum key_input_type
  {
    KEY_INPUT_TYPE_INVALID = 0,

    KEY_INPUT_TYPE_FIRST_VALID,
    KEY_INPUT_TYPE_EXIT = KEY_INPUT_TYPE_FIRST_VALID,

    KEY_INPUT_TYPE_CAMERA_RESET,
    KEY_INPUT_TYPE_CAMERA_PITCH_UP,
    KEY_INPUT_TYPE_CAMERA_PITCH_DOWN,
    KEY_INPUT_TYPE_CAMERA_ROLL_RIGHT,
    KEY_INPUT_TYPE_CAMERA_ROLL_LEFT,
    KEY_INPUT_TYPE_CAMERA_YAW_RIGHT,
    KEY_INPUT_TYPE_CAMERA_YAW_LEFT,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_UP,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_DOWN,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_RIGHT,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_LEFT,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_FORWARD,
    KEY_INPUT_TYPE_CAMERA_TRANSLATE_BACKWARD,

    KEY_INPUT_TYPE_LAST_VALID = KEY_INPUT_TYPE_CAMERA_TRANSLATE_BACKWARD,
    KEY_INPUT_TYPE_COUNT,
  };

  /**
   * Class responsible for managing keyboard input.
   */
  class key_input
  {
  public:

    key_input();

    bool input_active(key_input_type type) const;
    void key_pressed(int key, int scancode, int action, int mods);

  private:

    static const int GLFW_KEY_COUNT = GLFW_KEY_LAST + 1;

    key_input_type m_type_mod_none[GLFW_KEY_COUNT];
    key_input_type m_type_mod_shift[GLFW_KEY_COUNT];
    key_input_type m_type_mod_ctrl[GLFW_KEY_COUNT];
    key_input_type m_type_mod_alt[GLFW_KEY_COUNT];
    bool m_key_active[KEY_INPUT_TYPE_COUNT];

    key_input(const key_input& other) = delete;
    key_input& operator =(const key_input& other) = delete;

    void init_key_map();
    void handle_press(int key, int mods);
    void handle_release(int key, int mods);
    void set_input_type_active(key_input_type type, bool active);

  };

}

#endif /* KEY_INPUT_HPP */
