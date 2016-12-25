/**
 * @file	trivial_state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include <iostream>
#include <glm/glm.hpp>

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "app/state/trivial_state_manager.hpp"
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
  update_background_color(args);
}

void trivial_state_manager::command_activated(ogl::input_command command)
{
}

void trivial_state_manager::command_deactivated(ogl::input_command command)
{
  // no-op
}

void trivial_state_manager::update_background_color(const state_run_args& args)
{
  const auto delta = COLOR_PER_SECOND * args.delta_t;

  // update background color
  if (args.input_manager->command_active(input_command::color_red_increase))
    m_background_color.r += delta;
  if (args.input_manager->command_active(input_command::color_red_decrease))
    m_background_color.r -= delta;
  if (args.input_manager->command_active(input_command::color_green_increase))
    m_background_color.g += delta;
  if (args.input_manager->command_active(input_command::color_green_decrease))
    m_background_color.g -= delta;
  if (args.input_manager->command_active(input_command::color_blue_increase))
    m_background_color.b += delta;
  if (args.input_manager->command_active(input_command::color_blue_decrease))
    m_background_color.b -= delta;

  // clamp components to valid range
  m_background_color.r = clamp(m_background_color.r, COLOR_MINIMUM, COLOR_MAXIMUM);
  m_background_color.g = clamp(m_background_color.g, COLOR_MINIMUM, COLOR_MAXIMUM);
  m_background_color.b = clamp(m_background_color.b, COLOR_MINIMUM, COLOR_MAXIMUM);
}
