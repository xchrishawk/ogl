/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "app/application.hpp"
#include "app/input_manager.hpp"
#include "app/renderer.hpp"
#include "glfw/glfw.hpp"
#include "glfw/window.hpp"
#include "opengl/api.hpp"
#include "opengl/error.hpp"
#include "opengl/opengl.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application()
  : m_glfw(),
    m_window(window::create(true,
			    constants::WINDOW_INITIAL_WIDTH,
			    constants::WINDOW_INITIAL_HEIGHT,
			    constants::WINDOW_TITLE)),
    m_opengl(),
    m_input_manager(),
    m_state_manager(),
    m_renderer()
{
  if (application::s_instance)
  {
    ogl_dbg_error("Attempted to initialize application while it was already initialized!");
    ogl::fail();
  }

  m_glfw.set_swap_interval(constants::OPENGL_SWAP_INTERVAL);
  m_window->set_key_callback(application::key_callback);

  m_input_manager.add_input_key_observer(this);
  m_input_manager.add_input_key_observer(&m_state_manager);

  application::s_instance = this;
  ogl_dbg_status("Application initialized successfully.");
}

application::~application()
{
  m_input_manager.remove_input_key_observer(this);
  m_input_manager.remove_input_key_observer(&m_state_manager);

  application::s_instance = nullptr;
  ogl_dbg_status("Application shutting down...");
}

void application::main()
{
  auto last_state_t = m_glfw.time();
  auto last_render_t = m_glfw.time();

  while (!m_window->should_close())
  {
    // handle user input every loop
    handle_input();

    // get timing info
    auto abs_t = m_glfw.time();

    // handle state updates
    auto state_delta_t = abs_t - last_state_t;
    if (state_delta_t >= constants::TARGET_STATE_DELTA_T)
    {
      handle_state(abs_t, state_delta_t);
      last_state_t = abs_t;
    }

    // handle rendering
    auto render_delta_t = abs_t - last_render_t;
    if (render_delta_t >= constants::TARGET_RENDER_DELTA_T)
    {
      handle_render(abs_t, render_delta_t);
      last_render_t = abs_t;
    }
  }
}

void application::input_key_pressed(input_key input)
{
  switch (input)
  {
  case INPUT_KEY_APPLICATION_EXIT:
    m_window->set_should_close(true);
    break;

  default:
    break;
  }
}

void application::handle_input()
{
  m_glfw.poll_events();
}

void application::handle_state(double abs_t, double delta_t)
{
}

void application::handle_render(double abs_t, double delta_t)
{
  // get dimensions of framebuffer
  auto fb_width = 0, fb_height = 0;
  m_window->framebuffer_size(&fb_width, &fb_height);

  // create arguments with required data
  render_args args(abs_t, delta_t, fb_width, fb_height);

  // render and swap buffers
  m_renderer.render(args);
  m_window->swap_buffers();

#if defined(OGL_DEBUG)

  // if this is a debug build, check for errors
  auto error = ogl::opengl_last_error();
  if (error != GL_NO_ERROR)
    ogl_dbg_warning("OpenGL error detected in run loop!", opengl_error_string(error));

#endif /* OGL_DEBUG */
}

void application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (application::s_instance)
    application::s_instance->m_input_manager.handle_key(key, scancode, action, mods);
}
