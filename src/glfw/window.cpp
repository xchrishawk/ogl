/**
 * @file	window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

/* -- Includes -- */

#include "glfw/window.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Procedures -- */

window::window(const window_args& args)
  : app::window(),
    api_(args.api),
    window_manager_(args.window_manager)
{
  if (!api_)
    throw std::invalid_argument("API may not be null!");
  if (!window_manager_)
    throw std::invalid_argument("Window manager may not be null!");
}

window::~window()
{
}
