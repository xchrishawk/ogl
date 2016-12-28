/**
 * @file	window_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Procedures -- */

ogl::window_manager::ptr window_manager::create(const window_manager_args& args)
{
  return ogl::window_manager::ptr(new window_manager(args));
}

window_manager::window_manager(const window_manager_args& args)
{
}

window_manager::~window_manager()
{
}
