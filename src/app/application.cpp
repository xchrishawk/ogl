/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "app/input_manager.hpp"
#include "app/render_manager.hpp"
#include "app/resource_manager.hpp"
#include "app/state_manager.hpp"
#include "opengl/opengl.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"
#include "window/window_manager.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application(const application_args& args)
  : m_window_manager(args.window_manager),
    m_window(args.window),
    m_opengl(args.opengl),
    m_input_manager(args.input_manager),
    m_resource_manager(args.resource_manager),
    m_state_manager(args.state_manager),
    m_render_manager(args.render_manager),
    m_target_state_delta_t(args.target_state_delta_t),
    m_target_render_delta_t(args.target_render_delta_t)
{
  if (application::s_instance)
  {
    ogl_dbg_error("Attempted to initialize application while it is already initialized!");
    ogl::fail();
  }

  // register data flow for inputs
  m_window->add_key_observer(m_input_manager.get());
  m_input_manager->add_observer(this);

  application::s_instance = this;
  ogl_dbg_status("Application launched successfully.");

#if defined(OGL_DEBUG)
  prototype_test();
#endif /* defined (OGL_DEBUG) */
}

application::~application()
{
  // clean up input data flow
  m_window->remove_key_observer(m_input_manager.get());
  m_input_manager->remove_observer(this);

  application::s_instance = nullptr;
  ogl_dbg_status("Terminating application...");
}

void application::main()
{
  ogl_dbg_status("Running application main loop...");

  double last_state_t = m_window_manager->time();
  double last_render_t = m_window_manager->time();

  // loop until the main window needs to close
  while (!m_window->should_close())
  {
    // run input every cycle
    run_input();

    // get current absolute time
    double abs_t = m_window_manager->time();

    // run state if needed
    double state_delta_t = abs_t - last_state_t;
    if (state_delta_t > m_target_state_delta_t)
    {
      run_state(abs_t, state_delta_t);
      last_state_t = abs_t;
    }

    // run rendering if needed
    double render_delta_t = abs_t - last_render_t;
    if (render_delta_t > m_target_render_delta_t)
    {
      run_render(abs_t, render_delta_t);
      last_render_t = abs_t;
    }
  }

  ogl_dbg_status("Application main loop exited.");
}

void application::command_activated(input_command key)
{
  switch (key)
  {
  case input_command::application_exit:
    // this will terminate the main run loop, resulting in the app closing
    m_window->set_should_close(true);
    break;

  default:
    break;
  }
}

void application::command_deactivated(input_command key)
{
  // no-op
}

void application::run_input()
{
  // get events from the window manager
  m_window_manager->poll_events();
}

void application::run_state(double abs_t, double delta_t)
{
  // create args
  state_run_args args;
  args.abs_t = abs_t;
  args.delta_t = delta_t;

  // run the state loop
  m_state_manager->run(args);
}

void application::run_render(double abs_t, double delta_t)
{
  // create args
  render_run_args args;
  args.abs_t = abs_t;
  args.delta_t = delta_t;
  args.state_manager = m_state_manager;
  args.opengl = m_opengl;

  // run the render loop
  m_render_manager->run(args);

  // swap buffers to display new rendered image
  m_window->swap_buffers();

#if defined(OGL_DEBUG)
  // check for errors in debug builds
  GLenum error = m_opengl->last_error();
  if (error != GL_NO_ERROR)
  {
    ogl_dbg_warning("Unexpected OpenGL error: " + m_opengl->error_string(error));
  }
#endif
}

#if defined(OGL_DEBUG)

void application::prototype_test() const
{
}

#endif /* defined(OGL_DEBUG) */
