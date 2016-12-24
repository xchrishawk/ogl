/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application(const application_args& args)
  : m_window_manager(args.window_manager),
    m_window(args.window)
{
  if (application::s_instance)
  {
    ogl_dbg_error("Attempted to initialize application while it is already initialized!");
    ogl::fail();
  }

  application::s_instance = this;
  ogl_dbg_status("Application launched successfully.");
}

application::~application()
{
  application::s_instance = nullptr;
  ogl_dbg_status("Terminating application...");
}

void application::main()
{
  ogl_dbg_status("Running application...");
}
