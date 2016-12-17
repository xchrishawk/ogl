/**
 * @file	input.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cstring>
#include <iostream>

#include <GLFW/glfw3.h>

#include "app/input.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input::input()
{
  memset(m_type_mod_none, 0, sizeof(m_type_mod_none));
  memset(m_type_mod_shift, 0, sizeof(m_type_mod_shift));
  memset(m_type_mod_ctrl, 0, sizeof(m_type_mod_ctrl));
  memset(m_type_mod_alt, 0, sizeof(m_type_mod_alt));
  memset(m_key_active, 0, sizeof(m_key_active));

  init_key_map();
}

bool input::input_active(input_key key) const
{
  ogl_assert(input_key_valid(key));
  return m_key_active[key];
}

void input::init_key_map()
{
  // no modifier active
  m_type_mod_none[GLFW_KEY_ESCAPE]	= INPUT_KEY_EXIT_APPLICATION;
  m_type_mod_none[GLFW_KEY_X]		= INPUT_KEY_CAMERA_RESET;
  m_type_mod_none[GLFW_KEY_R]		= INPUT_KEY_CAMERA_TRANSLATE_UP;
  m_type_mod_none[GLFW_KEY_F]		= INPUT_KEY_CAMERA_TRANSLATE_DOWN;
  m_type_mod_none[GLFW_KEY_D]		= INPUT_KEY_CAMERA_TRANSLATE_RIGHT;
  m_type_mod_none[GLFW_KEY_A]		= INPUT_KEY_CAMERA_TRANSLATE_LEFT;
  m_type_mod_none[GLFW_KEY_W]		= INPUT_KEY_CAMERA_TRANSLATE_FORWARD;
  m_type_mod_none[GLFW_KEY_S]		= INPUT_KEY_CAMERA_TRANSLATE_BACKWARD;
  m_type_mod_none[GLFW_KEY_Y]		= INPUT_KEY_CAMERA_FOV_DECREASE;
  m_type_mod_none[GLFW_KEY_U]		= INPUT_KEY_CAMERA_FOV_INCREASE;

  // shift modifier active
  m_type_mod_shift[GLFW_KEY_S]		= INPUT_KEY_CAMERA_PITCH_UP;
  m_type_mod_shift[GLFW_KEY_W]		= INPUT_KEY_CAMERA_PITCH_DOWN;
  m_type_mod_shift[GLFW_KEY_E]		= INPUT_KEY_CAMERA_ROLL_RIGHT;
  m_type_mod_shift[GLFW_KEY_Q]		= INPUT_KEY_CAMERA_ROLL_LEFT;
  m_type_mod_shift[GLFW_KEY_D]		= INPUT_KEY_CAMERA_YAW_RIGHT;
  m_type_mod_shift[GLFW_KEY_A]		= INPUT_KEY_CAMERA_YAW_LEFT;
}

void input::key_pressed(int key, int scancode, int action, int mods)
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

void input::handle_press(int key, int mods)
{
  input_key type = INPUT_KEY_INVALID;
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
  set_input_key_active(type, true);
}

void input::handle_release(int key, int mods)
{
  // deactivate all inputs associated with the key
  set_input_key_active(m_type_mod_none[key], false);
  set_input_key_active(m_type_mod_shift[key], false);
  set_input_key_active(m_type_mod_ctrl[key], false);
  set_input_key_active(m_type_mod_alt[key], false);
}

void input::set_input_key_active(input_key key, bool active)
{
  if (key == INPUT_KEY_INVALID)
    return;

  ogl_assert(input_key_valid(key));
  m_key_active[key] = active;
}
