/**
 * @file	glfw_window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <sstream>

#include <GLFW/glfw3.h>

#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"
#include "window/glfw/glfw_interface.hpp"
#include "window/glfw/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl::glfw;

/* -- Variables -- */

// Since GLFW doesn't give us a reference pointer of any type when getting a callback,
// we have to keep track of the mapping from GLFWwindow* pointer to glfw_window object
// instance so we can correctly distribute events.
std::map<const GLFWwindow*, const glfw_window*> glfw_window::s_lookup;

/* -- Procedure Prototypes -- */

namespace
{
  /** Converts a GLFW key enum to a `window_key` enum. */
  ogl::window_key glfw_to_window_key(int key);

  /** Converts a GLFW modifier enum to a `window_key_modifier` enum. */
  ogl::window_key_modifier glfw_to_window_key_modifier(int mods);

  /** Converts a GLFW action enum to a `window_key_action` enum. */
  ogl::window_key_action glfw_to_window_key_action(int action);
}

/* -- Procedures -- */

ogl::window::ptr glfw_window::create(const glfw_window_args& args)
{
  return ogl::window::ptr(new glfw_window(args));
}

glfw_window::glfw_window(const glfw_window_args& args)
  : window(),
    m_handle(nullptr)
{
  // create handle
  m_handle = glfwCreateWindow(args.width,		// width
			      args.height,		// height
			      args.title.c_str(),	// title
			      NULL,			// monitor
			      NULL);			// share
  if (!m_handle)
    throw std::runtime_error("Failed to create GLFW window.");

  // register for callbacks
  glfw_window::s_lookup[m_handle] = this;
  glfwSetKeyCallback(m_handle, glfw_window::key_callback);

#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW window created - " << glfw_window::s_lookup.size() << " window(s) active.";
  ogl_dbg_status(message.str());
#endif
}

glfw_window::~glfw_window()
{
  // destroy handle
  glfwDestroyWindow(m_handle);

  // unregister for callbacks
  glfw_window::s_lookup.erase(m_handle);
  m_handle = nullptr;

#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW window destroyed - " << glfw_window::s_lookup.size() << " window(s) active.";
  ogl_dbg_status(message.str());
#endif
}

bool glfw_window::is_current_context() const
{
  return (glfwGetCurrentContext() == m_handle);
}

void glfw_window::make_current_context()
{
  glfwMakeContextCurrent(m_handle);
}

void glfw_window::swap_buffers()
{
  glfwSwapBuffers(m_handle);
}

bool glfw_window::should_close() const
{
  return glfw_boolean_to_bool(glfwWindowShouldClose(m_handle));
}

void glfw_window::set_should_close(bool should_close)
{
  glfwSetWindowShouldClose(m_handle, bool_to_glfw_boolean(should_close));
}

std::string glfw_window::title() const
{
  // GLFW does not give us a way to get the title
  return m_title;
}

void glfw_window::set_title(const std::string& title)
{
  glfwSetWindowTitle(m_handle, title.c_str());
  m_title = title;
}

void glfw_window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // make sure we can find a matching object for this GLFWwindow* pointer
  auto it = s_lookup.find(window);
  if (it != s_lookup.end())
  {
    // convert key
    const auto ogl_key = glfw_to_window_key(key);
    if (ogl_key == ogl::window_key::invalid)
      return;

    // convert modifier
    const auto ogl_mod = glfw_to_window_key_modifier(mods);
    if (ogl_mod == ogl::window_key_modifier::invalid)
      return;

    // convert action
    const auto ogl_action = glfw_to_window_key_action(action);
    if (ogl_action == ogl::window_key_action::invalid)
      return;

    // notify observers
    it->second->notify_key(ogl_key, ogl_mod, ogl_action);
  }
  else
    ogl_dbg_assert_fail("Received key notification from an unrecognized window!");
}

/* -- Private Procedures -- */

namespace
{
  ogl::window_key glfw_to_window_key(int key)
  {
    // special case for unknown key
    if (key == GLFW_KEY_UNKNOWN)
      return ogl::window_key::invalid;

    static const auto GLFW_KEY_COUNT = GLFW_KEY_LAST + 1;
    ogl_dbg_assert(key >= 0 && key < GLFW_KEY_COUNT);

    // lazy initialization of keymap
    static auto initialized = false;
    static ogl::window_key keymap[GLFW_KEY_COUNT] = { ogl::window_key::invalid };
    if (!initialized)
    {
      keymap[GLFW_KEY_ESCAPE]		= ogl::window_key::escape;
      keymap[GLFW_KEY_A]		= ogl::window_key::letter_a;
      keymap[GLFW_KEY_B]		= ogl::window_key::letter_b;
      keymap[GLFW_KEY_C]		= ogl::window_key::letter_c;
      keymap[GLFW_KEY_D]		= ogl::window_key::letter_d;
      keymap[GLFW_KEY_E]		= ogl::window_key::letter_e;
      keymap[GLFW_KEY_F]		= ogl::window_key::letter_f;
      keymap[GLFW_KEY_G]		= ogl::window_key::letter_g;
      keymap[GLFW_KEY_H]		= ogl::window_key::letter_h;
      keymap[GLFW_KEY_I]		= ogl::window_key::letter_i;
      keymap[GLFW_KEY_J]		= ogl::window_key::letter_j;
      keymap[GLFW_KEY_K]		= ogl::window_key::letter_k;
      keymap[GLFW_KEY_L]		= ogl::window_key::letter_l;
      keymap[GLFW_KEY_M]		= ogl::window_key::letter_m;
      keymap[GLFW_KEY_N]		= ogl::window_key::letter_n;
      keymap[GLFW_KEY_O]		= ogl::window_key::letter_o;
      keymap[GLFW_KEY_P]		= ogl::window_key::letter_p;
      keymap[GLFW_KEY_Q]		= ogl::window_key::letter_q;
      keymap[GLFW_KEY_R]		= ogl::window_key::letter_r;
      keymap[GLFW_KEY_S]		= ogl::window_key::letter_s;
      keymap[GLFW_KEY_T]		= ogl::window_key::letter_t;
      keymap[GLFW_KEY_U]		= ogl::window_key::letter_u;
      keymap[GLFW_KEY_V]		= ogl::window_key::letter_v;
      keymap[GLFW_KEY_W]		= ogl::window_key::letter_w;
      keymap[GLFW_KEY_X]		= ogl::window_key::letter_x;
      keymap[GLFW_KEY_Y]		= ogl::window_key::letter_y;
      keymap[GLFW_KEY_Z]		= ogl::window_key::letter_z;
      keymap[GLFW_KEY_0]		= ogl::window_key::digit_0;
      keymap[GLFW_KEY_1]		= ogl::window_key::digit_1;
      keymap[GLFW_KEY_2]		= ogl::window_key::digit_2;
      keymap[GLFW_KEY_3]		= ogl::window_key::digit_3;
      keymap[GLFW_KEY_4]		= ogl::window_key::digit_4;
      keymap[GLFW_KEY_5]		= ogl::window_key::digit_5;
      keymap[GLFW_KEY_6]		= ogl::window_key::digit_6;
      keymap[GLFW_KEY_7]		= ogl::window_key::digit_7;
      keymap[GLFW_KEY_8]		= ogl::window_key::digit_8;
      keymap[GLFW_KEY_9]		= ogl::window_key::digit_9;
    }

    return keymap[key];
  }

  ogl::window_key_modifier glfw_to_window_key_modifier(int mods)
  {
    switch (mods)
    {
    case 0:
      return ogl::window_key_modifier::none;
    case GLFW_MOD_SHIFT:
      return ogl::window_key_modifier::shift;
    case GLFW_MOD_CONTROL:
      return ogl::window_key_modifier::control;
    case GLFW_MOD_ALT:
      return ogl::window_key_modifier::alt;
    case GLFW_MOD_SUPER:
      return ogl::window_key_modifier::super;
    default:
      // currently we don't support more than one modifier active at a time.
      // yes, I know this is lame.
      return ogl::window_key_modifier::invalid;
    }
  }

  ogl::window_key_action glfw_to_window_key_action(int action)
  {
    switch (action)
    {
    case GLFW_PRESS:
      return ogl::window_key_action::press;
    case GLFW_RELEASE:
      return ogl::window_key_action::release;
    default:
      return ogl::window_key_action::invalid;
    }
  }
}
