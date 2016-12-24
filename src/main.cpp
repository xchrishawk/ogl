/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <exception>

#include <GLFW/glfw3.h>

#include "app/application.hpp"
#include "opengl/opengl.hpp"
#include "opengl/glew/glew_interface.hpp"
#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/window_manager.hpp"
#include "window/glfw/glfw_interface.hpp"
#include "window/glfw/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  /** Create application args using GLFW and GLEW. */
  application_args application_args_glfw();
}

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    auto args = application_args_glfw();
    application app(args);
    app.main();
    return 0;
  }
  catch (const std::exception& ex)
  {
    ogl_dbg_assert_fail("Uncaught exception!", ex.what());
    return 1;
  }
}

namespace
{
  application_args application_args_glfw()
  {
    application_args args;

    // window manager is GLFW
    args.window_manager = glfw::glfw_interface::create();

    // window is a GLFW window
    glfw::glfw_window_args window_args;
    window_args.title 				= "OGL";
    window_args.width 				= 1024;
    window_args.height 				= 768;
    window_args.opengl_profile			= GLFW_OPENGL_CORE_PROFILE;
    window_args.opengl_forward_compat		= GL_TRUE;
    window_args.opengl_context_version_major	= 3;
    window_args.opengl_context_version_minor	= 3;
    window_args.opengl_msaa_samples		= 4;
    args.window = glfw::glfw_window::create(window_args);
    args.window->make_current_context();

    // OpenGL uses GLEW
    args.opengl = glew::glew_interface::create();

    return args;
  }
}
