/**
 * @file	trivial_state_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include "app/state_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Basic trivial state manager object.
   */
  class trivial_state_manager : public state_manager
  {
  public:

    /** Creates a shared pointer to a new `trivial_state_manager` instance. */
    static state_manager::ptr create();

    ~trivial_state_manager();

    /* -- `state_manager` Interface Implementation -- */

    virtual void run(const ogl::state_run_args& args);

    /* -- `input_observer` Interface Implementation -- */

    virtual void command_activated(ogl::input_command command);
    virtual void command_deactivated(ogl::input_command command);

  private:

    trivial_state_manager();

  };

}
