/**
 * @file	input_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <algorithm>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "app/input_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input_manager::input_manager()
  : m_input_keys { false },
    m_input_key_observers()
{
}

void input_manager::handle_key(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
    handle_key_press(key, mods);
  else if (action == GLFW_RELEASE)
    handle_key_release(key, mods);
}

bool input_manager::input_key_state(input_key input) const
{
  ogl_dbg_assert(input_key_valid(input));
  return m_input_keys[input];
}

void input_manager::add_input_key_observer(input_key_observer* observer)
{
  m_input_key_observers.push_back(observer);
}

void input_manager::remove_input_key_observer(input_key_observer* observer)
{
  auto it = std::find(m_input_key_observers.begin(), m_input_key_observers.end(), observer);
  if (it != m_input_key_observers.end())
    m_input_key_observers.erase(it);
}

void input_manager::handle_key_press(int key, int mods)
{
  // make sure this is a valid keypress, and get the corresponding input
  auto input = input_key_for_key(key, mods);
  if (input == INPUT_KEY_INVALID)
    return;

  // set the state for this input
  m_input_keys[input] = true;

  // notify observers if we need to
  if (should_notify_input_key(input))
    notify_input_key(input);
}

void input_manager::handle_key_release(int key, int mods)
{
  // clear every input for this key
  input_key input;
  if ((input = input_key_for_key(key, 0)) != INPUT_KEY_INVALID)
    m_input_keys[input] = false;
  if ((input = input_key_for_key(key, GLFW_MOD_SHIFT)) != INPUT_KEY_INVALID)
    m_input_keys[input] = false;
  if ((input = input_key_for_key(key, GLFW_MOD_CONTROL)) != INPUT_KEY_INVALID)
    m_input_keys[input] = false;
  if ((input = input_key_for_key(key, GLFW_MOD_ALT)) != INPUT_KEY_INVALID)
    m_input_keys[input] = false;
  if ((input = input_key_for_key(key, GLFW_MOD_SUPER)) != INPUT_KEY_INVALID)
    m_input_keys[input] = false;
}

void input_manager::notify_input_key(input_key key)
{
  for (auto observer : m_input_key_observers)
    observer->input_key_pressed(key);
}

input_key input_manager::input_key_for_key(int key, int mods)
{
  switch (mods)
  {
  case 0:
    // no mods
    switch (key)
    {
    case GLFW_KEY_ESCAPE:     	return INPUT_KEY_APPLICATION_EXIT;
    case GLFW_KEY_F1:		return INPUT_KEY_CONTROL_MODE_CAMERA;
    case GLFW_KEY_F2:		return INPUT_KEY_CONTROL_MODE_OBJECT;
    case GLFW_KEY_TAB:		return INPUT_KEY_CONTROL_OBJECT_CYCLE;
    case GLFW_KEY_X:		return INPUT_KEY_CAMERA_RESET;
    case GLFW_KEY_W:	 	return INPUT_KEY_TRANSLATE_FORWARD;
    case GLFW_KEY_S:      	return INPUT_KEY_TRANSLATE_BACKWARD;
    case GLFW_KEY_D:      	return INPUT_KEY_TRANSLATE_RIGHT;
    case GLFW_KEY_A:      	return INPUT_KEY_TRANSLATE_LEFT;
    case GLFW_KEY_R:      	return INPUT_KEY_TRANSLATE_UP;
    case GLFW_KEY_F:      	return INPUT_KEY_TRANSLATE_DOWN;
    case GLFW_KEY_C:		return INPUT_KEY_SCALE_UP;
    case GLFW_KEY_Z:		return INPUT_KEY_SCALE_DOWN;
    default:      		return INPUT_KEY_INVALID;
    }

  case GLFW_MOD_SHIFT:
    // shift key active
    switch (key)
    {
    case GLFW_KEY_W:		return INPUT_KEY_ROTATE_PITCH_DOWN;
    case GLFW_KEY_S:		return INPUT_KEY_ROTATE_PITCH_UP;
    case GLFW_KEY_D:		return INPUT_KEY_ROTATE_YAW_RIGHT;
    case GLFW_KEY_A:		return INPUT_KEY_ROTATE_YAW_LEFT;
    case GLFW_KEY_E:		return INPUT_KEY_ROTATE_ROLL_RIGHT;
    case GLFW_KEY_Q:		return INPUT_KEY_ROTATE_ROLL_LEFT;
    default:			return INPUT_KEY_INVALID;
    }

  default:
    // unknown mod
    return INPUT_KEY_INVALID;
  }
}

bool input_manager::should_notify_input_key(input_key key)
{
  switch (key)
  {
  case INPUT_KEY_APPLICATION_EXIT:
  case INPUT_KEY_CONTROL_MODE_CAMERA:
  case INPUT_KEY_CONTROL_MODE_OBJECT:
  case INPUT_KEY_CONTROL_OBJECT_CYCLE:
  case INPUT_KEY_CAMERA_RESET:
    return true;

  default:
    return false;
  }
}

bool input_manager::input_key_valid(input_key key)
{
  return (static_cast<int>(key) >= static_cast<int>(INPUT_KEY_FIRST_VALID) &&
	  static_cast<int>(key) <= static_cast<int>(INPUT_KEY_LAST_VALID));
}
