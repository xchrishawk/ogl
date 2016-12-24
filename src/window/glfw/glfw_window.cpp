/**
 * @file	glfw_window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/glfw/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Procedures -- */

ogl::window::ptr glfw_window::create()
{
  return ogl::window::ptr(new glfw_window());
}

glfw_window::glfw_window()
  : m_handle(nullptr)
{
  ogl_dbg_status("GLFW window created.");
}

glfw_window::~glfw_window()
{
  ogl_dbg_status("GLFW window destroyed.");
}
