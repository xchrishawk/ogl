/**
 * main.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <exception>
#include <sstream>
#include <string>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    application::instance().main();
    return EXIT_SUCCESS;
  }
  catch (const std::exception& ex)
  {
    std::ostringstream message;
    message << "Uncaught exception: " << ex.what();
    ogl_fail_message(message.str());
    return EXIT_FAILURE;
  }
}
