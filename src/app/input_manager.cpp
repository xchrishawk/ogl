/**
 * @file	input_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

/* -- Includes -- */

#include <algorithm>
#include <memory>
#include <vector>

#include "app/input_manager.hpp"
#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input_manager::ptr input_manager::create()
{
  return input_manager::ptr(new input_manager());
}

input_manager::input_manager()
{
}

void input_manager::add_observer(input_observer* observer) const
{
  m_observers.push_back(observer);
}

void input_manager::remove_observer(input_observer* observer) const
{
  m_observers.erase(
    std::remove(m_observers.begin(), m_observers.end(), observer),
    m_observers.end());
}

void input_manager::window_key_pressed(const ogl::window* window,
				       ogl::window_key key,
				       ogl::window_key_action action)
{
  input_command the_input_command = window_key_to_input_command(key);
  if (the_input_command == input_command::invalid)
    return;

  int index = static_cast<int>(the_input_command);

  switch (action)
  {
  case window_key_action::press:
    m_key_active[index] = true;
    notify_input_command_activated(the_input_command);
    break;

  case window_key_action::release:
    m_key_active[index] = false;
    notify_input_command_deactivated(the_input_command);
    break;

  default:
    ogl_dbg_assert_fail("Unknown key action type!");
    return;
  }
}

input_command input_manager::window_key_to_input_command(window_key key)
{
  switch (key)
  {
  case window_key::escape:
    return input_command::application_exit;
  default:
    return input_command::invalid;
  }
}

void input_manager::notify_input_command_activated(input_command key) const
{
  for (input_observer* observer : m_observers)
    observer->input_command_activated(key);
}

void input_manager::notify_input_command_deactivated(input_command key) const
{
  for (input_observer* observer : m_observers)
    observer->input_command_deactivated(key);
}
