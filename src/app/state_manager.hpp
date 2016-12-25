/**
 * @file	state_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include "app/input_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to run a loop of the state manager.
   */
  struct state_run_args
  {
    double abs_t;
    double delta_t;
    ogl::input_manager::const_ptr input_manager;
  };

  /**
   * Abstract interface for types representing the state of the application.
   */
  class state_manager : public input_observer
  {
  public:

    /** Shared pointer to a `state_manager` object. */
    typedef std::shared_ptr<state_manager> ptr;

    /** Shared pointer to a `cosnt state_manager` object. */
    typedef std::shared_ptr<const state_manager> const_ptr;

    virtual ~state_manager() { }

    /**
     * Runs a loop of the state object.
     *
     * @param args
     * Arguments object containing information required to run the loop.
     */
    virtual void run(const state_run_args& args) = 0;

  protected:

    state_manager() { }

  private:

    state_manager(const state_manager&) = delete;
    state_manager& operator =(const state_manager&) = delete;

  };

}
