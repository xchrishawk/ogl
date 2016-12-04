/**
 * glfw.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <csignal>
#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glfw.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Variables -- */

bool glfw::initialized = false;

/* -- Procedures -- */

glfw::glfw()
{
  ogl_assert(!glfw::initialized);

  glfwSetErrorCallback(glfw::error_callback);
  if (!glfwInit())
    throw runtime_error("Failed to initialize GLFW library.");

  glfw::initialized = true;
  ogl_trace_message("GLFW initialized.");
}

glfw::~glfw()
{
  glfwTerminate();
  glfwSetErrorCallback(nullptr);

  glfw::initialized = false;
  ogl_trace_message("GLFW terminated.");
}

void glfw::version(int* major, int* minor, int* revision) const
{
  glfwGetVersion(major, minor, revision);
}

string glfw::version_string() const
{
  return string(glfwGetVersionString());
}

void glfw::error_callback(int error, const char* description)
{
#ifdef OGL_DEBUG
  std::cerr << "*** GLFW Error " << error << " - " << description << endl;
  std::raise(SIGINT);
#endif
}
