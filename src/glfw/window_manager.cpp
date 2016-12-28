/**
 * @file	window_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/debug.hpp"
#include "util/exceptions.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Variables -- */

window_manager* window_manager::instance_s = nullptr;

/* -- Procedures -- */

ogl::window_manager::ptr window_manager::create(const window_manager_args& args)
{
  return ogl::window_manager::ptr(new window_manager(args));
}

window_manager::window_manager(const window_manager_args& args)
{
  if (window_manager::instance_s != nullptr)
    throw ogl::duplicate_object_exception("Attempted to initialize GLFW when it is already initialized!");

  window_manager::instance_s = this;
  ogl_dbg_status("GLFW initialized.");
}

window_manager::~window_manager()
{
  window_manager::instance_s = nullptr;
  ogl_dbg_status("GLFW terminated.");
}
