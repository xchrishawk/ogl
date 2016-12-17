/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application()
  : m_input(),
    m_state(),
    m_renderer()
{
  if (application::s_instance)
  {
    ogl_debug_print_always("Attempted to initialize application while it was already initialized!");
    ogl::fail();
  }

  application::s_instance = this;
  ogl_debug_print("Application initialized successfully.");
}

application::~application()
{
  application::s_instance = nullptr;
  ogl_debug_print("Application shutting down...");
}

void application::main()
{
}

void application::handle_input(double abs_t, double delta_t)
{
}

void application::handle_state(double abs_t, double delta_t)
{
}

void application::handle_render(double abs_t, double delta_t)
{
}
