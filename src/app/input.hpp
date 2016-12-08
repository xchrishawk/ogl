/**
 * input.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_INPUT_HPP
#define OGL_APP_INPUT_HPP

/* -- Includes -- */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* -- Types -- */

namespace ogl
{

  // forward declaration
  class application;

  /**
   * Enumeration of input keys.
   */
  enum input_key
  {
    INPUT_KEY_INVALID = 0,
    INPUT_KEY_FIRST_VALID,
    INPUT_KEY_EXIT_APPLICATION = INPUT_KEY_FIRST_VALID,
    INPUT_KEY_CAMERA_RESET,
    INPUT_KEY_CAMERA_TRANSLATE_UP,
    INPUT_KEY_CAMERA_TRANSLATE_DOWN,
    INPUT_KEY_CAMERA_TRANSLATE_RIGHT,
    INPUT_KEY_CAMERA_TRANSLATE_LEFT,
    INPUT_KEY_CAMERA_TRANSLATE_FORWARD,
    INPUT_KEY_CAMERA_TRANSLATE_BACKWARD,
    INPUT_KEY_CAMERA_PITCH_UP,
    INPUT_KEY_CAMERA_PITCH_DOWN,
    INPUT_KEY_CAMERA_ROLL_RIGHT,
    INPUT_KEY_CAMERA_ROLL_LEFT,
    INPUT_KEY_CAMERA_YAW_RIGHT,
    INPUT_KEY_CAMERA_YAW_LEFT,
    INPUT_KEY_CAMERA_FOV_INCREASE,
    INPUT_KEY_CAMERA_FOV_DECREASE,
    INPUT_KEY_LAST_VALID = INPUT_KEY_CAMERA_FOV_DECREASE,
    INPUT_KEY_COUNT,
  };

  /**
   * User input interface class.
   */
  class input
  {
  public:

    input();

    bool input_active(input_key key) const;

    friend class ogl::application;

  private:

    static const int GLFW_KEY_COUNT = GLFW_KEY_LAST + 1;

    input_key m_type_mod_none[GLFW_KEY_COUNT];
    input_key m_type_mod_shift[GLFW_KEY_COUNT];
    input_key m_type_mod_ctrl[GLFW_KEY_COUNT];
    input_key m_type_mod_alt[GLFW_KEY_COUNT];
    bool m_key_active[INPUT_KEY_COUNT];

    input(const input& other) = delete;
    input& operator =(const input& other) = delete;

    void init_key_map();
    void key_pressed(int key, int scancode, int action, int mods);
    void handle_press(int key, int mods);
    void handle_release(int key, int mods);
    void set_input_key_active(input_key key, bool active);

  };

}

/* -- Procedures -- */

namespace ogl
{

  inline bool input_key_valid(input_key key)
  {
    return (static_cast<int>(key) >= static_cast<int>(INPUT_KEY_FIRST_VALID) &&
	    static_cast<int>(key) <= static_cast<int>(INPUT_KEY_LAST_VALID));
  }

}

#endif /* OGL_APP_INPUT_HPP */
