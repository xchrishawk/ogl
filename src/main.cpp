/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
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
    #warning FIX
//    ogl_debug_print("*** Uncaught exception!");
//    ogl_debug_print(ex.what());
//    ogl::fail();
  }
}
