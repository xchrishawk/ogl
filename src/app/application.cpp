/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "app/application.hpp"
#include "app/input.hpp"
#include "app/renderer.hpp"
#include "app/state.hpp"
#include "opengl/error.hpp"
#include "opengl/glew.hpp"
#include "opengl/glfw.hpp"
#include "opengl/window.hpp"
#include "util/debug.hpp"

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
  static application instance;
  return instance;
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
    m_input(),
    m_state(),
    m_renderer()
{
  ogl_trace_message("Application launched successfully.");
}

application::~application()
{
  ogl_trace_message("Application terminated.");
}

void application::main()
{
  float last_state_t = time();
  float last_render_t = time();

  while (!m_window.should_close())
  {
    // poll GLFW window events
    window::poll_events();

    // handle application-level inputs
    handle_app_input();

    float abs_t = time();

    // perform state updates if needed
    float state_delta_t = abs_t - last_state_t;
    if (state_delta_t >= TARGET_STATE_RATE)
    {
      handle_state(abs_t, state_delta_t);
      last_state_t = abs_t;
    }

    // perform rendering if needed
    float render_delta_t = abs_t - last_render_t;
    if (render_delta_t >= TARGET_RENDER_RATE)
    {
      handle_render(abs_t, render_delta_t);
      last_render_t = abs_t;
    }
  }
}

float application::time() const
{
  return static_cast<float>(glfwGetTime());
}

void application::handle_app_input()
{
  if (m_input.input_active(INPUT_KEY_EXIT_APPLICATION))
    m_window.set_should_close(true);
}

void application::handle_state(float abs_t, float delta_t)
{
  m_state.update(abs_t, delta_t, m_input);
}

void application::handle_render(float abs_t, float delta_t)
{
  // get framebuffer size
  int width = 0;
  int height = 0;
  m_window.framebuffer_size(&width, &height);

  // render the display
  m_renderer.render(width, height, m_state);
  m_window.swap_buffers();

  // check for OpenGL errors
#ifdef OGL_DEBUG
  GLenum last_error = opengl_last_error();
  if (last_error != GL_NO_ERROR)
    ogl_error_message(opengl_error_string(last_error));
#endif /* OGL_DEBUG */
}

void application::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  instance().m_input.key_pressed(key, scancode, action, mods);
}
