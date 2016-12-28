/**
 * @file	init_glfw.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "app/application.hpp"
#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "ogl/init_glfw.hpp"

/* -- Procedures -- */

void ogl::init_application_args_glfw_window_manager(ogl::application_args& args)
{
  glfw::window_manager_args window_manager_args;

  args.window_manager = glfw::window_manager::create(window_manager_args);
}
