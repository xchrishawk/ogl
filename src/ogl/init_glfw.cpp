/**
 * @file	init_glfw.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <memory>

#include "app/application.hpp"
#include "app/window_manager.hpp"
#include "glfw/api.hpp"
#include "glfw/window.hpp"
#include "glfw/window_manager.hpp"
#include "ogl/init_glfw.hpp"

/* -- Procedures -- */

void ogl::init_application_args_glfw(app::application_args& args)
{
  // create API
  auto api = glfw::api::create();

  // create window manager
  glfw::window_manager_args window_manager_args;
  window_manager_args.api = api;
  auto window_manager = glfw::window_manager::create(window_manager_args);

  // create window
  glfw::window_args window_args;
  window_args.api = api;
  window_args.window_manager = window_manager;
  auto window = glfw::window::create(window_args);

  // configure app args
  args.window_manager = window_manager;
  args.window = window;
}
