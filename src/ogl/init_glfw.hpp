/**
 * @file	init_glfw.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include "app/application.hpp"

/* -- Types -- */

namespace ogl
{

  /** Initializes the specified application arguments with a GLFW window manager and window. */
  void init_application_args_glfw(app::application_args& args);

}
