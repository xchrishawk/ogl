/**
 * key_input.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef KEY_INPUT_HPP
#define KEY_INPUT_HPP

/* -- Types -- */

namespace ogl
{

  /**
   * Enumeration of available key presses.
   */
  enum key_input_type
  {
    KEY_INPUT_TYPE_INVALID = -1,
    KEY_INPUT_TYPE_FIRST = 0,
    KEY_INPUT_TYPE_EXIT = KEY_INPUT_TYPE_FIRST,
    KEY_INPUT_TYPE_COUNT,
  };

  /**
   * Class responsible for managing keyboard input.
   */
  class key_input
  {
  public:

    key_input();

    bool input_active(key_input_type type) const;
    void key_pressed(int key, int scancode, int action, int mods);

  private:

    bool m_key_active[KEY_INPUT_TYPE_COUNT];

    key_input(const key_input& other) = delete;
    key_input& operator =(const key_input& other) = delete;

    key_input_type type_for_key_press(int key, int mods);

  };

}

#endif /* KEY_INPUT_HPP */
