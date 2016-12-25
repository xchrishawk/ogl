/**
 * @file	window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

/* -- Includes -- */

#include <algorithm>
#include <vector>

#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

void window::add_key_observer(window_key_observer* observer) const
{
  ogl_dbg_assert(observer != nullptr);
  m_key_observers.push_back(observer);
}

void window::remove_key_observer(window_key_observer* observer) const
{
  ogl_dbg_assert(observer != nullptr);
  m_key_observers.erase(
    std::remove(m_key_observers.begin(), m_key_observers.end(), observer),
    m_key_observers.end());
}

void window::notify_key(window_key key, window_key_action action) const
{
  for (auto& observer : m_key_observers)
    observer->window_key_pressed(this, key, action);
}
