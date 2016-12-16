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

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_int() << std::endl;

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_int(15) << std::endl;

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_float() << std::endl;

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_float(10.0f) << std::endl;

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_double() << std::endl;

  for (int idx = 0; idx < 10; idx++)
    std::cout << ogl::random_double(200.0) << std::endl;

  std::cout << "hello ogl" << std::endl;
  return 0;
}
