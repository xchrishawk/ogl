/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <exception>

#include <GLFW/glfw3.h>

#include "app/application.hpp"
#include "app/input_manager.hpp"
#include "app/render_manager.hpp"
#include "app/resource_manager.hpp"
#include "app/state_manager.hpp"
#include "app/simple/render_manager.hpp"
#include "app/simple/state_manager.hpp"
#include "opengl/opengl.hpp"
#include "opengl/impl/opengl_interface.hpp"
#include "util/debug.hpp"
#include "window/window.hpp"
#include "window/window_manager.hpp"
#include "window/impl/glfw_interface.hpp"
#include "window/impl/glfw_window.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  void init_window_manager_glfw(application_args& args);
  void init_window_glfw(application_args& args);
  void init_opengl_glew(application_args& args);
  void init_input_manager(application_args& args);
  void init_resource_manager(application_args& args);
  void init_state_manager_simple(application_args& args);
  void init_render_manager_simple(application_args& args);
}

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    // configure application
    application_args args;
    init_window_manager_glfw(args);
    init_window_glfw(args);
    init_opengl_glew(args);
    init_input_manager(args);
    init_resource_manager(args);
    init_state_manager_simple(args);
    init_render_manager_simple(args);

    // final app configuration
    args.target_state_delta_t = (1.0 / 60.0);
    args.target_render_delta_t = (1.0 / 60.0);

    // run application
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
  void init_window_manager_glfw(application_args& args)
  {
    // arguments for GLFW interface
    impl::glfw_interface_args glfw_interface_args;
    glfw_interface_args.opengl_profile			= GLFW_OPENGL_CORE_PROFILE;
    glfw_interface_args.opengl_forward_compat		= GL_TRUE;
    glfw_interface_args.opengl_context_version_major	= 3;
    glfw_interface_args.opengl_context_version_minor	= 3;
    glfw_interface_args.opengl_msaa_samples		= 4;

    // create GLFW interface
    impl::glfw_interface::ptr glfw_interface = impl::glfw_interface::create(glfw_interface_args);
    args.window_manager 				= glfw_interface;
  }

  void init_window_glfw(application_args& args)
  {
    // arguments for GLFW window
    impl::glfw_window_args glfw_window_args;
    glfw_window_args.title 				= "OGL";
    glfw_window_args.width 				= 1024;
    glfw_window_args.height 				= 768;

    // create GLFW window
    impl::glfw_window::ptr glfw_window = impl::glfw_window::create(glfw_window_args);
    glfw_window->make_current_context();
    args.window 					= glfw_window;
  }

  void init_opengl_glew(application_args& args)
  {
    // create OpenGL/GLEW interface
    impl::opengl_interface::ptr opengl = impl::opengl_interface::create();
    args.opengl = opengl;
  }

  void init_input_manager(application_args& args)
  {
    // create default input manager
    input_manager::ptr input_manager = input_manager::create();
    args.input_manager = input_manager;
  }

  void init_resource_manager(application_args& args)
  {
    // create default resource manager
    resource_manager::ptr resource_manager = resource_manager::create();
    args.resource_manager = resource_manager;
  }

  void init_state_manager_simple(application_args& args)
  {
    // state manager args
    simple::state_manager_args state_manager_args;
    state_manager_args.input_manager = args.input_manager;
    state_manager_args.resource_manager = args.resource_manager;

    // create state manager
    state_manager::ptr state_manager = simple::state_manager::create(state_manager_args);
    args.state_manager = state_manager;
  }

  void init_render_manager_simple(application_args& args)
  {
    // render manager args
    simple::render_manager_args render_manager_args;
    render_manager_args.resource_manager = args.resource_manager;

    // create render manager
    render_manager::ptr render_manager = simple::render_manager::create(render_manager_args);
    args.render_manager = render_manager;
  }
}
