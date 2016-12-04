/**
 * key_input.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "key_input.hpp"
#include "opengl.hpp"
#include "util.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

key_input::key_input()
{
  for (int type = static_cast<int>(KEY_INPUT_TYPE_FIRST); type < static_cast<int>(KEY_INPUT_TYPE_COUNT); type++)
    m_key_active[index] = false;
}

bool key_input::input_active(key_input_type type) const
{
  ogl_assert(static_cast<int>(type) >= static_cast<int>(KEY_INPUT_TYPE_FIRST));
  ogl_assert(static_cast<int>(type) < static_cast<int>(KEY_INPUT_TYPE_LAST));
  return m_key_active[type];
}

void key_input::key_pressed(int key, int scancode, int action, int mods)
{
  bool new_state;
  switch (action)
  {
  case GLFW_PRESS:
    new_state = true;
    break;
  case GLFW_RELEASE:
    new_state = false;
    break;
  default:
    /* ignore GLFW_REPEAT events */
    return;
  }

  key_input_type type = type_for_key_press(key, mods);
  if (type != KEY_INPUT_TYPE_INVALID)
    m_key_active[type] = new_state;
}

key_input_type key_input::type_for_key_press(int key, int mods)
{
  static const int GLFW_MOD_NONE = 0;

  switch (mods)
  {
  case GLFW_MOD_NONE:
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
      return KEY_INPUT_TYPE_EXIT;
    default:
      return KEY_INPUT_TYPE_INVALID;
    }

  default:
    return KEY_INPUT_TYPE_INVALID;
  }
}
