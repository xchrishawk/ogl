/**
 * @file	glfw_interface.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "util/debug.hpp"
#include "window/window_manager.hpp"
#include "window/glfw/glfw_interface.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Variables -- */

glfw_interface* glfw_interface::s_instance = nullptr;

/* -- Procedures -- */

ogl::window_manager::ptr glfw_interface::create()
{
  return ogl::window_manager::ptr(new glfw_interface());
}

glfw_interface::glfw_interface()
  : window_manager()
{
  if (glfw_interface::s_instance)
  {
    ogl_dbg_error("Attempted to initialize GLFW while it is already initialized!");
    ogl::fail();
  }

  glfwSetErrorCallback(glfw_interface::error_callback);
  if (!glfwInit())
    throw std::runtime_error("Unable to initialize GLFW.");

  glfw_interface::s_instance = this;
  ogl_dbg_status("GLFW initialized.", "Version:\t" + version());
}

glfw_interface::~glfw_interface()
{
  glfwTerminate();

  glfw_interface::s_instance = nullptr;
  ogl_dbg_status("GLFW terminated.");
}

std::string glfw_interface::version() const
{
  return std::string(glfwGetVersionString());
}

double glfw_interface::time() const
{
  return glfwGetTime();
}

void glfw_interface::poll_events() const
{
  glfwPollEvents();
}

void glfw_interface::error_callback(int error, const char* description)
{
#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW error code " << error << ": " << description;
  ogl_dbg_warning(message.str());
  ogl_dbg_breakpoint();
#endif
}
