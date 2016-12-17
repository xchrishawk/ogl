/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>
#include <GLFW/glfw3.h>

#include "app/application.hpp"
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
    m_glew(),
    m_input(),
    m_state(),
    m_renderer()
{
  if (application::s_instance)
  {
    ogl_debug_print_always("Attempted to initialize application while it was already initialized!");
    ogl::fail();
  }

  m_glfw.set_swap_interval(constants::OPENGL_SWAP_INTERVAL);
  m_window->set_key_callback(application::key_callback);

  application::s_instance = this;
  ogl_debug_print("Application initialized successfully.");
}

application::~application()
{
  application::s_instance = nullptr;
  ogl_debug_print("Application shutting down...");
}

void application::main()
{
  double last_t = m_glfw.time();
  double last_input_t = last_t;
  double last_state_t = last_t;
  double last_render_t = last_t;

  while (!m_window->should_close())
  {
    // get time statistics
    double abs_t = m_glfw.time();
    double delta_t = abs_t - last_t;
    last_t = abs_t;

    // handle user input
    if (abs_t - last_input_t >= constants::TARGET_INPUT_DELTA_T)
    {
      handle_input(abs_t, delta_t);
      last_input_t = abs_t;
    }

    // handle state updates
    if (abs_t - last_state_t >= constants::TARGET_STATE_DELTA_T)
    {
      handle_state(abs_t, delta_t);
      last_state_t = abs_t;
    }

    // handle rendering
    if (abs_t - last_render_t >= constants::TARGET_RENDER_DELTA_T)
    {
      handle_render(abs_t, delta_t);
      last_render_t = abs_t;
    }
  }
}

void application::handle_input(double abs_t, double delta_t)
{
  // poll GLFW events
  m_glfw.poll_events();

  // set the window close flag if the user selects to exit
  if (m_input.input_active(INPUT_KEY_EXIT_APPLICATION))
    m_window->set_should_close(true);
}

void application::handle_state(double abs_t, double delta_t)
{
  // create arguments with required data
  state_args args(m_input, abs_t, delta_t);

  // update state
  m_state.run(args);
}

void application::handle_render(double abs_t, double delta_t)
{
  // create arguments with required data
  render_args args(m_state, abs_t, delta_t);

  // render and swap buffers
  m_renderer.render(args);
  m_window->swap_buffers();
}

void application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // this gets farmed out to the input object
  if (s_instance)
    s_instance->m_input.key_pressed(key, scancode, action, mods);
}
