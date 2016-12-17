/**
 * @file	window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>

#include "glfw/window.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

window::ptr window::create(bool make_current,
			   int initial_width,
			   int initial_height,
			   const std::string& initial_title)
{
  return window::ptr(new window(make_current, initial_width, initial_height, initial_title));
}

window::window(bool make_current,
	       int initial_width,
	       int initial_height,
	       const std::string& initial_title)
  : m_handle(nullptr)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  m_handle = glfwCreateWindow(initial_width,		// width
			      initial_height,		// height
			      initial_title.c_str(),	// title
			      NULL,			// monitor
			      NULL);			// share
  if (!m_handle)
    throw std::runtime_error("Failed to create GLFW window!");

  if (make_current)
    make_context_current();
}

window::~window()
{
  glfwDestroyWindow(m_handle);
  m_handle = nullptr;
}

bool window::should_close() const
{
  return static_cast<bool>(glfwWindowShouldClose(m_handle));
}

void window::set_should_close(bool should_close)
{
  glfwSetWindowShouldClose(m_handle, static_cast<int>(should_close));
}

void window::swap_buffers()
{
  glfwSwapBuffers(m_handle);
}

void window::set_key_callback(GLFWkeyfun callback)
{
  glfwSetKeyCallback(m_handle, callback);
}

void window::make_context_current()
{
  glfwMakeContextCurrent(m_handle);
}

bool window::is_context_current() const
{
  return (glfwGetCurrentContext() == m_handle);
}
