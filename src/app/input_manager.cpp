/**
 * @file	input_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <iostream>

#include <GLFW/glfw3.h>

#include "app/input_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input_manager::input_manager()
  : m_input_keys { false }
{
}

void input_manager::handle_key(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
    handle_key_press(key, mods);
  else if (action == GLFW_RELEASE)
    handle_key_release(key, mods);
}

void input_manager::handle_key_press(int key, int mods)
{
  // make sure this is a valid keypress, and get the corresponding input
  input_key input = input_key_for_key(key, mods);
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

input_key input_manager::input_key_for_key(int key, int mods)
{
  if (key == GLFW_KEY_ESCAPE)
    return INPUT_KEY_APPLICATION_EXIT;
  else
    return INPUT_KEY_INVALID;
}

bool input_manager::should_notify_input_key(input_key key)
{
  switch (key)
  {
  case INPUT_KEY_APPLICATION_EXIT:
  case INPUT_KEY_CAMERA_RESET:
    return true;

  default:
    return false;
  }
}

void input_manager::notify_input_key(input_key key)
{
  // TODO
}

bool input_manager::input_key_valid(input_key key)
{
  return (static_cast<int>(key) >= static_cast<int>(INPUT_KEY_FIRST_VALID) &&
	  static_cast<int>(key) <= static_cast<int>(INPUT_KEY_LAST_VALID));
}
