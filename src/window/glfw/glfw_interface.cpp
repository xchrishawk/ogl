/**
 * @file	glfw_interface.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include "util/debug.hpp"
#include "window/window_manager.hpp"
#include "window/glfw/glfw_interface.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Procedures -- */

ogl::window_manager::ptr glfw_interface::create()
{
  return ogl::window_manager::ptr(new glfw_interface());
}

glfw_interface::glfw_interface()
  : window_manager()
{
  ogl_dbg_status("GLFW initialized.");
}

glfw_interface::~glfw_interface()
{
  ogl_dbg_status("GLFW terminated.");
}
