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
#include "window/impl/glfw_interface.hpp"

/* -- Namespaces -- */

using namespace ogl::impl;

/* -- Variables -- */

glfw_interface* glfw_interface::s_instance = nullptr;

/* -- Procedures -- */

ogl::window_manager::ptr glfw_interface::create(const glfw_interface_args& args)
{
  return ogl::window_manager::ptr(new glfw_interface(args));
}

glfw_interface::glfw_interface(const glfw_interface_args& args)
  : window_manager()
{
  if (glfw_interface::s_instance)
  {
    ogl_dbg_error("Attempted to initialize GLFW while it is already initialized!");
    ogl::fail();
  }

  glfwSetErrorCallback(glfw_interface::error_callback);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW.");

  glfwWindowHint(GLFW_OPENGL_PROFILE, args.opengl_profile);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, args.opengl_forward_compat);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, args.opengl_context_version_major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, args.opengl_context_version_minor);
  glfwWindowHint(GLFW_SAMPLES, args.opengl_msaa_samples);

  glfw_interface::s_instance = this;
  ogl_dbg_status("GLFW initialized.", "API Version:\t\t" + version());
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
