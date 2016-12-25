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
  // TEMP
  notify_input_key_activated(input_key::application_exit);
}

void input_manager::notify_input_key_activated(input_key key) const
{
  for (input_observer* observer : m_observers)
    observer->input_key_activated(key);
}

void input_manager::notify_input_key_deactivated(input_key key) const
{
  for (input_observer* observer : m_observers)
    observer->input_key_deactivated(key);
}
