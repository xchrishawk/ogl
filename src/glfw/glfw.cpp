/**
 * @file	glfw.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include "glfw/glfw.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

glfw::glfw()
{
  ogl_debug_print("GLFW initialized.");
}

glfw::~glfw()
{
  ogl_debug_print("GLFW terminated.");
}
