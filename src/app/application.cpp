/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace app;

/* -- Procedures -- */

application::application(const application_args& args)
  : window_manager_(args.window_manager),
    window_(args.window)
{
  if (!window_manager_)
    throw std::invalid_argument("Window manager may not be null!");
  if (!window_)
    throw std::invalid_argument("Window may not be null!");

  ogl_dbg_status("Application launched successfully.");
}

application::~application()
{
  ogl_dbg_status("Terminating application...");
}

void application::main()
{
  ogl_dbg_status("Running application...");

  while (!window_->should_close())
  {
    window_manager_->poll_events();
  }

  ogl_dbg_status("Main loop exited.");
}
