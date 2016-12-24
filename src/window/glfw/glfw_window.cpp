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

ogl::window::ptr glfw_window::create(const glfw_window_args& args)
{
  return ogl::window::ptr(new glfw_window(args));
}

glfw_window::glfw_window(const glfw_window_args& args)
  : m_handle(nullptr)
{
  m_handle = glfwCreateWindow(1024,		// initial width (TEMP)
			      768,		// initial height (TEMP)
			      "OGL",		// initial title (TEMP)
			      NULL,		// monitor
			      NULL);		// share
  if (!m_handle)
    throw std::runtime_error("Failed to create GLFW window.");

  ogl_dbg_status("GLFW window created.");
}

glfw_window::~glfw_window()
{
  glfwDestroyWindow(m_handle);
  m_handle = nullptr;
  ogl_dbg_status("GLFW window destroyed.");
}
