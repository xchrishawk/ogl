/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

application& application::instance()
{
  static application instance;
  return instance;
}

application::application()
{
  ogl_trace_message("Application launched successfully.");
}

application::~application()
{
  ogl_trace_message("Application terminated.");
}

void application::main()
{
}
