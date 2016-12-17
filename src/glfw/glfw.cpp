/**
 * @file	glfw.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "glfw/glfw.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

glfw* glfw::s_instance = nullptr;

/* -- Procedures -- */

glfw::glfw()
{
  if (glfw::s_instance)
  {
    ogl_error_print_always("Attempted to initialize GLFW while it was already initialized!");
    ogl::fail();
  }

  glfwSetErrorCallback(glfw::error_callback);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");

  glfw::s_instance = this;
  ogl_debug_print("GLFW initialized.");
}

glfw::~glfw()
{
  glfwTerminate();

  glfw::s_instance = nullptr;
  ogl_debug_print("GLFW terminated.");
}

double glfw::time() const
{
  return glfwGetTime();
}

void glfw::poll_events() const
{
  glfwPollEvents();
}

void glfw::wait_events() const
{
  glfwWaitEvents();
}

void glfw::set_swap_interval(int interval)
{
  glfwSwapInterval(interval);
}

void glfw::error_callback(int error, const char* description)
{
  std::ostringstream message;
  message << "* GLFW error! Code " << error << " (" << description << ")";
  ogl_debug_print_always(message.str());
  ogl_breakpoint();
}
