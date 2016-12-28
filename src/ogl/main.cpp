/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <exception>

#include "app/application.hpp"
#include "ogl/init_glfw.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    // create and initialize arguments
    app::application_args app_args;
    init_application_args_glfw_window_manager(app_args);

    // create and run application
    auto app = app::application::create(app_args);
    app->main();
    return 0;
  }
  catch (const std::exception& ex)
  {
    ogl_dbg_error("Uncaught exception!", ex.what());
    ogl_dbg_fail();
    return 1;
  }
}
