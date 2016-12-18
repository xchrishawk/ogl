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
    #warning FIX
    // ogl_error_print_always("Attempted to initialize GLFW while it was already initialized!");
    // ogl::fail();
  }

  glfwSetErrorCallback(glfw::error_callback);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");

  glfw::s_instance = this;
  #warning FIX
  // ogl_debug_print("GLFW initialized.");
  print_version_info();
}

glfw::~glfw()
{
  glfwTerminate();

  glfw::s_instance = nullptr;
  #warning FIX
  // ogl_debug_print("GLFW terminated.");
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
  #warning FIX
  // std::ostringstream message;
  // message << "* GLFW error! Code " << error << " (" << description << ")";
  // ogl_debug_print_always(message.str());
  // ogl_breakpoint();
}

void glfw::print_version_info()
{
  #warning FIX
#if defined(OGL_DEBUG)
  // std::ostringstream output;
  // output << "  GLFW Version:   " << glfwGetVersionString();
  // ogl_debug_print(output.str());
#endif
}
