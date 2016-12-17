/**
 * @file	state.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "app/input.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to run a loop of the state object.
   */
  class state_args
  {
  public:

    state_args(const ogl::input& input, double abs_t, double delta_t)
      : input(input),
	abs_t(abs_t),
	delta_t(delta_t)
    { }

    const ogl::input& input;
    const double abs_t;
    const double delta_t;

  };

  /**
   * Class representing the current state of the application.
   */
  class state
  {
  public:

    state() { }

    /** Runs a loop of the state object. */
    void run(const state_args& args);

  private:

    state(const state&) = delete;
    state& operator =(const state&) = delete;

  };

}
