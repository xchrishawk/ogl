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

window::ptr window::create()
{
  return window::ptr(new window());
}

window::window()
  : m_handle(nullptr)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  m_handle = glfwCreateWindow(800, 600, "Test", NULL, NULL);
  if (!m_handle)
    throw std::runtime_error("Failed to create GLFW window!");

  // FIXME: these should probably go somewhere else?
  glfwMakeContextCurrent(m_handle);
}

window::~window()
{
  glfwDestroyWindow(m_handle);
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
