/**
 * random.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <ctime>

#include "util/random.hpp"

/* -- Procedures -- */

void ogl::random_init()
{
  srand(time(NULL));
}
