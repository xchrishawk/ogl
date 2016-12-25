/**
 * @file	trivial_state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "app/state/trivial_state_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

state_manager::ptr trivial_state_manager::create()
{
  return state_manager::ptr(new trivial_state_manager());
}

trivial_state_manager::trivial_state_manager()
{
}

trivial_state_manager::~trivial_state_manager()
{
}

void trivial_state_manager::run(const state_run_args& args)
{
}

void trivial_state_manager::command_activated(ogl::input_command command)
{
}

void trivial_state_manager::command_deactivated(ogl::input_command command)
{
  // no-op
}
