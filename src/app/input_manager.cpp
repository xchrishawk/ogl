/**
 * @file	input_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <iostream>

#include "app/input_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

void input_manager::handle_keypress(int key, int scancode, int action, int mods)
{
  std::cout << "key: " << key
	    << " scancode: " << scancode
	    << " action: " << action
	    << " mods: " << mods
	    << std::endl;
}
