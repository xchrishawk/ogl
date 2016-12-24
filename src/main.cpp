/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include "util/debug.hpp"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  ogl_dbg_status("Hello world!");
  ogl_dbg_assert(1 == 1);
  ogl_dbg_assert_fail("Barf");
  return 0;
}
