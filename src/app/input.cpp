/**
 * @file	input.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cstring>
#include <iostream>

#include "app/input.hpp"
#include "glfw/glfw.hpp"
#include "glfw/window.hpp"
#include "opengl/api.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

input::input(window::const_ptr window)
  : m_window(window)
{
}

void input::key_pressed(int key, int scancode, int action, int mods)
{
  // we don't do anything with repeat actions
  if (action == GLFW_REPEAT)
    return;
}
