/**
 * @file	main.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  ogl_dbg_status("Hello there!");
  ogl_dbg_status("This message", "has multiple lines");
  ogl_dbg_warning("This is a warning");
  ogl_dbg_error("This is an error");

  ogl_assert(1 == 1);
  ogl_assert_fail("Failed assert");

  return 0;
}
