/**
 * key_input.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstring>
#include <iostream>

#include "key_input.hpp"
#include "opengl.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

key_input::key_input()
{
  memset(m_type_mod_none, 0, sizeof(m_type_mod_none));
  memset(m_type_mod_shift, 0, sizeof(m_type_mod_shift));
  memset(m_type_mod_ctrl, 0, sizeof(m_type_mod_ctrl));
  memset(m_type_mod_alt, 0, sizeof(m_type_mod_alt));
  memset(m_key_active, 0, sizeof(m_key_active));

  init_key_map();
}

bool key_input::input_active(key_input_type type) const
{
  ogl_assert(static_cast<int>(type) >= static_cast<int>(KEY_INPUT_TYPE_FIRST_VALID));
  ogl_assert(static_cast<int>(type) <= static_cast<int>(KEY_INPUT_TYPE_LAST_VALID));
  return m_key_active[type];
}

void key_input::key_pressed(int key, int scancode, int action, int mods)
{
  ogl_assert(key < GLFW_KEY_COUNT);
  switch (action)
  {
  case GLFW_PRESS:
    handle_press(key, mods);
    break;
  case GLFW_RELEASE:
    handle_release(key, mods);
    break;
  default:
    return;
  }
}

void key_input::init_key_map()
{
  // no modifier active
  m_type_mod_none[GLFW_KEY_ESCAPE]	= KEY_INPUT_TYPE_EXIT;
  m_type_mod_none[GLFW_KEY_X]		= KEY_INPUT_TYPE_CAMERA_RESET;
  m_type_mod_none[GLFW_KEY_R]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_UP;
  m_type_mod_none[GLFW_KEY_F]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_DOWN;
  m_type_mod_none[GLFW_KEY_D]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_RIGHT;
  m_type_mod_none[GLFW_KEY_A]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_LEFT;
  m_type_mod_none[GLFW_KEY_W]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_FORWARD;
  m_type_mod_none[GLFW_KEY_S]		= KEY_INPUT_TYPE_CAMERA_TRANSLATE_BACKWARD;

  // shift modifier active
  m_type_mod_shift[GLFW_KEY_S]		= KEY_INPUT_TYPE_CAMERA_PITCH_UP;
  m_type_mod_shift[GLFW_KEY_W]		= KEY_INPUT_TYPE_CAMERA_PITCH_DOWN;
  m_type_mod_shift[GLFW_KEY_E]		= KEY_INPUT_TYPE_CAMERA_ROLL_RIGHT;
  m_type_mod_shift[GLFW_KEY_Q]		= KEY_INPUT_TYPE_CAMERA_ROLL_LEFT;
  m_type_mod_shift[GLFW_KEY_D]		= KEY_INPUT_TYPE_CAMERA_YAW_RIGHT;
  m_type_mod_shift[GLFW_KEY_A]		= KEY_INPUT_TYPE_CAMERA_YAW_LEFT;
}

void key_input::handle_press(int key, int mods)
{
  key_input_type type = KEY_INPUT_TYPE_INVALID;
  switch (mods)
  {
  case 0:
    type = m_type_mod_none[key];
    break;
  case GLFW_MOD_SHIFT:
    type = m_type_mod_shift[key];
    break;
  case GLFW_MOD_CONTROL:
    type = m_type_mod_ctrl[key];
    break;
  case GLFW_MOD_ALT:
    type = m_type_mod_alt[key];
    break;
  }
  set_input_type_active(type, true);
}

void key_input::handle_release(int key, int mods)
{
  // deactivate all inputs associated with the key
  set_input_type_active(m_type_mod_none[key], false);
  set_input_type_active(m_type_mod_shift[key], false);
  set_input_type_active(m_type_mod_ctrl[key], false);
  set_input_type_active(m_type_mod_alt[key], false);
}

void key_input::set_input_type_active(key_input_type type, bool active)
{
  if (type == KEY_INPUT_TYPE_INVALID)
    return;

  ogl_assert(static_cast<int>(type) >= static_cast<int>(KEY_INPUT_TYPE_FIRST_VALID));
  ogl_assert(static_cast<int>(type) <= static_cast<int>(KEY_INPUT_TYPE_LAST_VALID));

  m_key_active[type] = active;
}
