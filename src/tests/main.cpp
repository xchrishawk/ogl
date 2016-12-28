/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>
#include "util/debug.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  ogl::debug::set_output_suppressed(true);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
