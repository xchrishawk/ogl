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
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

glfw::glfw()
{
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");

  ogl_debug_print("GLFW initialized.");
}

glfw::~glfw()
{
  glfwTerminate();
  ogl_debug_print("GLFW terminated.");
}

void glfw::error_callback(int error, const char* description)
{
  std::ostringstream message;
  message << "* GLFW error! Code " << error << " (" << description << ")";
  ogl_debug_print_always(message.str());
  ogl_breakpoint();
}
