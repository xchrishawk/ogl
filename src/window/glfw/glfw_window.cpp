/**
 * @file	glfw_window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/glfw/glfw_interface.hpp"
#include "window/glfw/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Procedures -- */

ogl::window::ptr glfw_window::create(const glfw_window_args& args)
{
  return ogl::window::ptr(new glfw_window(args));
}

glfw_window::glfw_window(const glfw_window_args& args)
  : window(),
    m_handle(nullptr)
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

bool glfw_window::should_close() const
{
  return glfw_boolean_to_bool(glfwWindowShouldClose(m_handle));
}

void glfw_window::set_should_close(bool should_close)
{
  glfwSetWindowShouldClose(m_handle, bool_to_glfw_boolean(should_close));
}

std::string glfw_window::title() const
{
  // GLFW does not give us a way to get the title
  return m_title;
}

void glfw_window::set_title(const std::string& title)
{
  glfwSetWindowTitle(m_handle, title.c_str());
  m_title = title;
}
