/**
 * main.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <exception>
#include <iostream>

#include "application.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    ogl::application::instance().main();
    return EXIT_SUCCESS;
  }
  catch (std::exception& ex)
  {
#ifdef OGL_DEBUG
    std::cerr << "*** Unhandled exception: " << ex.what() << std::endl;
#endif /*OGL_DEBUG */
    return EXIT_FAILURE;
  }
}
