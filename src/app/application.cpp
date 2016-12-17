/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

application::application()
  : m_glfw(),
    m_window(window::create())
{
  ogl_debug_print("Application initialized successfully.");
}

application::~application()
{
  ogl_debug_print("Application shutting down...");
}

void application::main()
{
  while (!m_window->should_close())
  {
    m_glfw.poll_events();
    m_window->swap_buffers();
  }
}
