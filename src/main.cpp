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

    // arguments for GLFW interface
    glfw::glfw_interface_args glfw_interface_args;
    glfw_interface_args.opengl_profile			= GLFW_OPENGL_CORE_PROFILE;
    glfw_interface_args.opengl_forward_compat		= GL_TRUE;
    glfw_interface_args.opengl_context_version_major	= 3;
    glfw_interface_args.opengl_context_version_minor	= 3;
    glfw_interface_args.opengl_msaa_samples		= 4;

    // create GLFW interface
    glfw::glfw_interface::ptr glfw_interface = glfw::glfw_interface::create(glfw_interface_args);
    args.window_manager = glfw_interface;

    // arguments for GLFW window
    glfw::glfw_window_args glfw_window_args;
    glfw_window_args.title 				= "OGL";
    glfw_window_args.width 				= 1024;
    glfw_window_args.height 				= 768;

    // create GLFW window
    glfw::glfw_window::ptr glfw_window = glfw::glfw_window::create(glfw_window_args);
    glfw_window->make_current_context();
    args.window = glfw_window;

    // create OpenGL/GLEW interface
    glew::glew_interface::ptr glew_interface = glew::glew_interface::create();
    args.opengl = glew_interface;

    return args;
  }
}
