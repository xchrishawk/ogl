/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <exception>

#include "app/application.hpp"
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
    window_args.title = "OGL";
    window_args.width = 1024;
    window_args.height = 768;
    args.window = glfw::glfw_window::create(window_args);

    return args;
  }

}
