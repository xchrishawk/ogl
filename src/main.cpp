/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <exception>

#include "app/application.hpp"
#include "util/debug.hpp"
#include "window/window_manager.hpp"
#include "window/glfw/glfw_interface.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    window_manager::ptr window_manager = glfw::glfw_interface::create();

    application app(window_manager);
    app.main();
    return 0;
  }
  catch (const std::exception& ex)
  {
    ogl_dbg_assert_fail("Uncaught exception!", ex.what());
    return 1;
  }
}
