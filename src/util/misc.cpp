/**
 * misc.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <ctime>

#include "util/misc.hpp"

/* -- Procedures -- */

int ogl::ogl_rand()
{
  static bool initialized = false;
  if (!initialized)
  {
    srand(time(nullptr));
    initialized = true;
  }
  return rand();
}

float ogl::ogl_randf()
{
  return static_cast<float>(ogl_rand()) / static_cast<float>(RAND_MAX);
}

double ogl::ogl_randd()
{
  return static_cast<double>(ogl_randd()) / static_cast<double>(RAND_MAX);
}
