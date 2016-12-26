/**
 * @file	state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include <iostream>
#include <glm/glm.hpp>

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "app/simple/state_manager.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const float COLOR_PER_SECOND = (1.0f / 3.0f);
  const float COLOR_MINIMUM = 0.0f;
  const float COLOR_MAXIMUM = 1.0f;
}

/* -- Procedures -- */

state_manager::ptr simple::state_manager::create(const simple::state_manager_args& args)
{
  return state_manager::ptr(new simple::state_manager(args));
}

simple::state_manager::state_manager(const simple::state_manager_args& args)
  : m_input_manager(args.input_manager),
    m_resource_manager(args.resource_manager),
    m_background_color()
{
  m_input_manager->add_observer(this);
}

simple::state_manager::~state_manager()
{
  m_input_manager->remove_observer(this);
}

void simple::state_manager::run(const state_run_args& args)
{
  update_background_color(args);
}

void simple::state_manager::command_activated(ogl::input_command command)
{
}

void simple::state_manager::command_deactivated(ogl::input_command command)
{
  // no-op
}

void simple::state_manager::update_background_color(const state_run_args& args)
{
  const auto delta = COLOR_PER_SECOND * args.delta_t;

  // update background color
  if (m_input_manager->command_active(input_command::color_red_increase))
    m_background_color.r += delta;
  if (m_input_manager->command_active(input_command::color_red_decrease))
    m_background_color.r -= delta;
  if (m_input_manager->command_active(input_command::color_green_increase))
    m_background_color.g += delta;
  if (m_input_manager->command_active(input_command::color_green_decrease))
    m_background_color.g -= delta;
  if (m_input_manager->command_active(input_command::color_blue_increase))
    m_background_color.b += delta;
  if (m_input_manager->command_active(input_command::color_blue_decrease))
    m_background_color.b -= delta;

  // clamp components to valid range
  m_background_color.r = clamp(m_background_color.r, COLOR_MINIMUM, COLOR_MAXIMUM);
  m_background_color.g = clamp(m_background_color.g, COLOR_MINIMUM, COLOR_MAXIMUM);
  m_background_color.b = clamp(m_background_color.b, COLOR_MINIMUM, COLOR_MAXIMUM);
}
