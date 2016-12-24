/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <iostream>

/* -- Procedures -- */

int main(int argc, char** argv)
{
#if defined(OGL_LINUX)
  std::cout << "Hello Linux!" << std::endl;
#elif defined(OGL_MACOS)
  std::cout << "Hello MacOS!" << std::endl;
#endif

#if defined(OGL_DEBUG)
  std::cout << "Hello Debug!" << std::endl;
#elif defined(OGL_RELEASE)
  std::cout << "Hello Release!" << std::endl;
#endif

  return 0;
}
