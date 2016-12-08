/**
 * main.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    application::instance().main();
    return EXIT_SUCCESS;
  }
  catch (exception& ex)
  {
#ifdef OGL_DEBUG
    ostringstream message;
    message << "Unhandled exception: " << ex.what();
    ogl_error_message(message.str());
#endif
    return EXIT_FAILURE;
  }
}
