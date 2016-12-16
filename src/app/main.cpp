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
#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    // required initialization objects
    glfw_factory glfw_fact;
    opengl_factory& ogl_fact = opengl_factory::platform_default();

    // create and run application
    application app(ogl_factory);
    app.main();

    // successful app run!
    return EXIT_SUCCESS;
  }
  catch (const std::exception& ex)
  {
    // print debug info if needed
#if defined(OGL_DEBUG)
    std::ostringstream message;
    message << "Uncaught exception: " << ex.what();
    ogl_fail_message(message.str());
#endif /* defined(OGL_DEBUG) */

    // failed...
    return EXIT_FAILURE;
  }
}
