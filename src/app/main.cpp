/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#include "util/strings.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  std::cout << ogl::stringf("Hello %s! The number is %d", "Chris", 42, "bongos", "what") << std::endl;
  return 0;
}
