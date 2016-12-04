/**
 * window.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>
#include <string>

#include "opengl.hpp"
#include "util.hpp"
#include "window.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

//window::window(int context_version_major, int context_version_minor)
window::window(int context_version_major,
	       int context_version_minor,
	       int initial_width,
	       int initial_height,
	       const string& initial_title)
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

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);

  ogl_trace_message("Window created");
}

window::~window()
{
  glfwSetKeyCallback(m_window, NULL);
  glfwDestroyWindow(m_window);

  ogl_trace_message("Window destroyed");
}

bool window::should_close() const
{
  return static_cast<bool>(glfwWindowShouldClose(m_window));
}

void window::swap_buffers() const
{
  glfwSwapBuffers(m_window);
}

void window::poll_events()
{
  glfwPollEvents();
}
