/**
 * @file	state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

state_manager::state_manager()
  : m_scene()
{
}

void state_manager::run(const state_loop_args& args)
{

}

void state_manager::input_key_pressed(input_key input)
{
  ogl_dbg_status("Hello!");
}
