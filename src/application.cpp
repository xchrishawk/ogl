/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <string>

#include "application.hpp"
#include "glfw.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const int TARGET_CONTEXT_VERSION_MAJOR = 3;
  const int TARGET_CONTEXT_VERSION_MINOR = 3;
  const int INITIAL_WINDOW_WIDTH = 800;
  const int INITIAL_WINDOW_HEIGHT = 600;
  const string INITIAL_WINDOW_TITLE = "OGL";

  const bool GLEW_USE_EXPERIMENTAL = true;

  const float TARGET_STATE_RATE = 1.0f / 60.0f;
  const float TARGET_RENDER_RATE = 1.0f / 60.0f;
}

/* -- Procedures -- */

application& application::instance()
{
  static application app;
  return app;
}

application::application()
  : m_glfw(),
    m_window(TARGET_CONTEXT_VERSION_MAJOR,
	     TARGET_CONTEXT_VERSION_MINOR,
	     INITIAL_WINDOW_WIDTH,
	     INITIAL_WINDOW_HEIGHT,
	     INITIAL_WINDOW_TITLE,
	     application::glfw_key_callback),
    m_glew(GLEW_USE_EXPERIMENTAL),
    m_key_input(),
    m_state(),
    m_renderer()
{
  ogl_trace_message("Application initialized");
}

application::~application()
{
  ogl_trace_message("Application closed");
}

void application::main()
{
  float prev_state_abs_t = time();
  float prev_render_abs_t = time();

  while (!m_window.should_close())
  {
    // poll events every loop
    window::poll_events();

    // check the current clock
    float abs_t = time();

    // run state loop if needed
    float state_delta_t = abs_t - prev_state_abs_t;
    if (state_delta_t >= TARGET_STATE_RATE)
    {
      state_loop(abs_t, state_delta_t);
      prev_state_abs_t = abs_t;
    }

    // run render loop if needed
    float render_delta_t = abs_t - prev_render_abs_t;
    if (render_delta_t >= TARGET_RENDER_RATE)
    {
      render_loop(abs_t, render_delta_t);
      prev_render_abs_t = abs_t;
    }
  }
}

float application::time()
{
  return (float)glfwGetTime();
}

void application::state_loop(float abs_t, float delta_t)
{
  // run a single loop of the state object
  m_state.loop(abs_t, delta_t, m_key_input);

  // set close flag if user requests it
  if (m_key_input.input_active(KEY_INPUT_TYPE_EXIT))
    m_window.set_should_close(true);
}

void application::render_loop(float abs_t, float delta_t)
{
  // draw scene and swap buffers
  m_renderer.loop(m_state);
  m_window.swap_buffers();
}

void application::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // key_input class handles this
  instance().m_key_input.key_pressed(key, scancode, action, mods);
}
