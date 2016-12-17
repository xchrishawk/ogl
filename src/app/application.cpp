
/**
 * @file	application.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <stdexcept>

#include <GL/glew.h>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  // timing information
  const double FREQ_60_HZ = (1.0 / 60.0);
  const double TARGET_INPUT_RATE = FREQ_60_HZ;
  const double TARGET_STATE_RATE = FREQ_60_HZ;
  const double TARGET_RENDER_RATE = FREQ_60_HZ;
}

/* -- Variables -- */

application* application::s_instance = nullptr;

/* -- Procedures -- */

application::application()
  : m_glfw(),
    m_window(window::create()),
    m_glew(),
    m_input(),
    m_state()
{
  if (application::s_instance)
  {
    ogl_debug_print_always("Attempted to initialize application while it was already initialized!");
    ogl::fail();
  }

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
    if (abs_t - last_input_t > TARGET_INPUT_RATE)
    {
      handle_input(abs_t, delta_t);
      last_input_t = abs_t;
    }

    // handle state updates
    if (abs_t - last_state_t > TARGET_STATE_RATE)
    {
      handle_state(abs_t, delta_t);
      last_state_t = abs_t;
    }

    // handle rendering
    if (abs_t - last_render_t > TARGET_RENDER_RATE)
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
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_window->swap_buffers();
}

void application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // this gets farmed out to the input object
  if (s_instance)
    s_instance->m_input.key_pressed(key, scancode, action, mods);
}
