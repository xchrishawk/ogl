/**
 * @file	glfw.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "glfw/glfw.hpp"
#include "opengl/api.hpp"
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
    ogl_dbg_error("Attempted to initialize GLFW while it was already initialized!");
    ogl::fail();
  }

  glfwSetErrorCallback(glfw::error_callback);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");

  glfw::s_instance = this;
  ogl_dbg_status("GLFW initialized.",
		 "Version:            " + version());
}

glfw::~glfw()
{
  glfwTerminate();

  glfw::s_instance = nullptr;
  ogl_dbg_status("GLFW terminated.");
}

std::string glfw::version() const
{
  return std::string(glfwGetVersionString());
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
  message << "GLFW error! Code " << error << " (" << description << ")";
  ogl_dbg_warning(message.str());
  ogl_dbg_breakpoint();
}
