/**
 * @file	glfw_window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <sstream>

#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/glfw/glfw_interface.hpp"
#include "window/glfw/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Variables -- */

// Since GLFW doesn't give us a reference pointer of any type when getting a callback,
// we have to keep track of the mapping from GLFWwindow* pointer to glfw_window object
// instance so we can correctly distribute events.
std::map<GLFWwindow*, glfw_window*> glfw_window::s_lookup;

/* -- Procedures -- */

ogl::window::ptr glfw_window::create(const glfw_window_args& args)
{
  return ogl::window::ptr(new glfw_window(args));
}

glfw_window::glfw_window(const glfw_window_args& args)
  : window(),
    m_handle(nullptr)
{
  // create handle
  m_handle = glfwCreateWindow(args.width,		// width
			      args.height,		// height
			      args.title.c_str(),	// title
			      NULL,			// monitor
			      NULL);			// share
  if (!m_handle)
    throw std::runtime_error("Failed to create GLFW window.");

  // register for callbacks
  glfw_window::s_lookup[m_handle] = this;
  glfwSetKeyCallback(m_handle, glfw_window::key_callback);

#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW window created - " << glfw_window::s_lookup.size() << " window(s) active.";
  ogl_dbg_status(message.str());
#endif
}

glfw_window::~glfw_window()
{
  // destroy handle
  glfwDestroyWindow(m_handle);

  // unregister for callbacks
  glfw_window::s_lookup.erase(m_handle);
  m_handle = nullptr;

#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW window destroyed - " << glfw_window::s_lookup.size() << " window(s) active.";
  ogl_dbg_status(message.str());
#endif
}

bool glfw_window::is_current_context() const
{
  return (glfwGetCurrentContext() == m_handle);
}

void glfw_window::make_current_context()
{
  glfwMakeContextCurrent(m_handle);
}

void glfw_window::swap_buffers()
{
  glfwSwapBuffers(m_handle);
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

void glfw_window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // make sure we can find a matching object for this GLFWwindow* pointer
  auto it = s_lookup.find(window);
  if (it != s_lookup.end())
    it->second->notify_key(window_key::invalid);
  else
    ogl_dbg_assert_fail("Received key notification from an unrecognized window!");
}
