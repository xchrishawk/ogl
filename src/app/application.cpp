/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

application::application(const application_args& args)
{
  ogl_dbg_status("Application launched successfully.");
}

application::~application()
{
  ogl_dbg_status("Terminating application...");
}

void application::main()
{
  ogl_dbg_status("Running application...");
}
