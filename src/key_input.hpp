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
   * Class responsible for managing keyboard input.
   */
  class key_input
  {
  public:

    key_input();
    void key_pressed(int key, int scancode, int action, int mods);

  private:

    key_input(const key_input& other) = delete;
    key_input& operator =(const key_input& other) = delete;

  };

}

#endif /* KEY_INPUT_HPP */
