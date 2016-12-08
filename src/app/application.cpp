/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "application.hpp"
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
    m_input()
{
  ogl_trace_message("Application launched successfully.");
}

application::~application()
{
  ogl_trace_message("Application terminated.");
}

void application::main()
{
  while (!m_window.should_close())
  {
    // poll GLFW window events
    window::poll_events();
  }
}

float application::time() const
{
  return static_cast<float>(glfwGetTime());
}

void application::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  instance().m_input.key_pressed(key, scancode, action, mods);
}
