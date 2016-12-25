/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

// <TEMP>
#include <GL/glew.h>
// </TEMP>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application(const application_args& args)
  : m_window_manager(args.window_manager),
    m_window(args.window),
    m_opengl(args.opengl),
    m_input_manager(args.input_manager)
{
  if (application::s_instance)
  {
    ogl_dbg_error("Attempted to initialize application while it is already initialized!");
    ogl::fail();
  }

  // register input manager as observer of window
  m_window->add_key_observer(m_input_manager.get());

  application::s_instance = this;
  ogl_dbg_status("Application launched successfully.");
}

application::~application()
{
  // clean up input registration
  m_window->remove_key_observer(m_input_manager.get());

  application::s_instance = nullptr;
  ogl_dbg_status("Terminating application...");
}

void application::main()
{
  ogl_dbg_status("Running application...");
  while (!m_window->should_close())
  {
    m_window_manager->poll_events();

    // <TEMP>
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // </TEMP>

    m_window->swap_buffers();
  }
}
