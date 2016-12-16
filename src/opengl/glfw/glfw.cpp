/**
 * glfw.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>

#include "opengl/api.hpp"
#include "opengl/glfw/glfw.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

glfw::glfw()
{
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");

  ogl_trace_message("GLFW initialized.");
}

glfw::~glfw()
{
  glfwTerminate();
  ogl_trace_message("GLFW shut down.");
}

glfw_factory& glfw_factory::platform_default()
{

}
