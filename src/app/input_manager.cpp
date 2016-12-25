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
#include "util/misc.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input_command input_command_map::command(window_key_modifier mod) const
{
  const auto index = static_cast<size_t>(mod);
  ogl_dbg_assert(index < sizeof(map));
  return map[index];
}

void input_command_map::set_command(window_key_modifier mod, input_command command)
{
  const auto index = static_cast<size_t>(mod);
  ogl_dbg_assert(index < sizeof(map));
  map[index] = command;
}

input_manager::ptr input_manager::create()
{
  return input_manager::ptr(new input_manager());
}

input_manager::input_manager()
  : m_command_map(enum_count<window_key>(), { input_command::invalid }),
    m_command_active(enum_count<input_command>(), false),
    m_observers()
{
  default_command_map();
}

void input_manager::add_observer(input_observer* observer) const
{
  ogl_dbg_assert(observer != nullptr);
  m_observers.push_back(observer);
}

void input_manager::remove_observer(input_observer* observer) const
{
  ogl_dbg_assert(observer != nullptr);
  m_observers.erase(
    std::remove(m_observers.begin(), m_observers.end(), observer),
    m_observers.end());
}

void input_manager::default_command_map()
{
  set_command(
    window_key::escape,
    window_key_modifier::none,
    input_command::application_exit);
}

input_command input_manager::command(window_key key, window_key_modifier mod) const
{
  size_t index = static_cast<size_t>(key);
  ogl_dbg_assert(index < m_command_map.size());
  return m_command_map[index].command(mod);
}

void input_manager::set_command(window_key key, window_key_modifier mod, input_command command)
{
  size_t index = static_cast<size_t>(key);
  ogl_dbg_assert(index < m_command_map.size());
  m_command_map[index].set_command(mod, command);
}

void input_manager::window_key_pressed(const ogl::window* window,
				       ogl::window_key key,
				       ogl::window_key_action action)
{
  input_command command = this->command(key, window_key_modifier::none);
  if (command == input_command::invalid)
    return;

  int index = static_cast<int>(command);

  switch (action)
  {
  case window_key_action::press:
    m_command_active[index] = true;
    notify_command_activated(command);
    break;

  case window_key_action::release:
    m_command_active[index] = false;
    notify_command_deactivated(command);
    break;

  default:
    ogl_dbg_assert_fail("Unknown key action type!");
    return;
  }
}

void input_manager::notify_command_activated(input_command key) const
{
  for (input_observer* observer : m_observers)
    observer->command_activated(key);
}

void input_manager::notify_command_deactivated(input_command key) const
{
  for (input_observer* observer : m_observers)
    observer->command_deactivated(key);
}
