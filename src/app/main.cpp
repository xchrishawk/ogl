/**
 * main.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>
#include "util/random.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  ogl::random_init();
  std::cout << "hello ogl" << std::endl;
  return 0;
}
