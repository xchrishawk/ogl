/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <exception>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    ogl::application app;
    app.main();
    return 0;
  }
  catch (const std::exception& ex)
  {
    ogl_dbg_assert_fail("Uncaught exception!", ex.what());
    return 1;
  }
}
