/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "application.hpp"
#include "glfw.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
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
    m_window(3, 3, 800, 800, "OGL"),	/* TODO: constants */
    m_glew(true)
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
    /* poll events every loop */
    window::poll_events();

    /* check current clock */
    float abs_t = time();

    /* run state if needed */
    float state_delta_t = abs_t - prev_state_abs_t;
    if (state_delta_t >= TARGET_STATE_RATE)
    {
      state_main(abs_t, state_delta_t);
      prev_state_abs_t = abs_t;
    }

    /* render if needed */
    float render_delta_t = abs_t - prev_render_abs_t;
    if (render_delta_t >= TARGET_RENDER_RATE)
    {
      render_main(abs_t, render_delta_t);
      prev_render_abs_t = abs_t;
    }
  }
}

float application::time()
{
  return (float)glfwGetTime();
}

void application::state_main(float abs_t, float delta_t)
{
}

void application::render_main(float abs_t, float delta_t)
{
  // TEMP
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  m_window.swap_buffers();
}
