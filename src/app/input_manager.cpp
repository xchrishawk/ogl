/**
 * @file	input_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

/* -- Includes -- */

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

void input_manager::window_key_pressed(const ogl::window* window,
				       ogl::window_key key,
				       ogl::window_key_action action)
{
  ogl_dbg_status("Key press received!");
}
