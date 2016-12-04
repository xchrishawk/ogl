/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "application.hpp"
#include "glfw.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

application& application::instance()
{
  static application app;
  return app;
}

application::application()
  : m_glfw()
{
  ogl_trace_message("Application initialized.");
}

application::~application()
{
  ogl_trace_message("Application closed.");
}

void application::main()
{
}
