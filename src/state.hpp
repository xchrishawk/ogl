/**
 * state.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef STATE_HPP
#define STATE_HPP

/* -- Includes -- */

#include "key_input.hpp"
#include "opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing the current state of the application.
   */
  class state
  {
  public:

    state();

    void loop(float abs_t, float delta_t, const key_input& key_input);

  private:

    state(const state& other) = delete;
    state& operator =(const state& other) = delete;

  };

}

#endif /* STATE_HPP */
