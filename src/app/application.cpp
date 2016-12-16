/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

application& application::instance()
{
  static application app;
  return app;
}

application::application()
{
  ogl_trace_message("Application launched successfully!");
}

application::~application()
{
  ogl_trace_message("Application terminating...");
}

void application::main()
{
  // TODO
  throw std::runtime_error("Application not implemented!");
}
