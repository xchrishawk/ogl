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
{
  ogl_debug_print("Application initialized successfully.");
}

application::~application()
{
  ogl_debug_print("Application shutting down...");
}

void application::main()
{
  throw std::runtime_error("App not implemented!");
}
