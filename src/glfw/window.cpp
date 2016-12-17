/**
 * @file	window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include "glfw/window.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

window::ptr window::create()
{
  return window::ptr(new window());
}

window::window()
{
}

window::~window()
{
}
