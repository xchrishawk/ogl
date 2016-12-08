/**
 * window.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "opengl/window.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

//window::window(int context_version_major, int context_version_minor)
window::window(int context_version_major,
	       int context_version_minor,
	       int initial_width,
	       int initial_height,
	       const string& initial_title,
	       GLFWkeyfun key_callback)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_version_major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_version_minor);

  m_window = glfwCreateWindow(initial_width,
			      initial_height,
			      initial_title.c_str(),
			      NULL,			/* monitor */
			      NULL);			/* share */
  if (!m_window)
    throw runtime_error("Failed to create GLFW window.");

  glfwSetKeyCallback(m_window, key_callback);
  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);
}

window::~window()
{
  glfwSetKeyCallback(m_window, NULL);
  glfwDestroyWindow(m_window);
}

bool window::should_close() const
{
  return static_cast<bool>(glfwWindowShouldClose(m_window));
}

void window::set_should_close(bool value)
{
  glfwSetWindowShouldClose(m_window, static_cast<int>(value));
}

void window::swap_buffers() const
{
  glfwSwapBuffers(m_window);
}

void window::framebuffer_size(int* width, int* height) const
{
  glfwGetFramebufferSize(m_window, width, height);
}

void window::poll_events()
{
  glfwPollEvents();
}
