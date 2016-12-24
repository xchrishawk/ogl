/**
 * @file	debug.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util/debug.hpp"

/* -- Procedures -- */

void ogl::fail()
{
  abort();
}

void ogl::breakpoint()
{
  std::raise(SIGINT);
}

std::string ogl::debug_message(const std::string& title,
			       const std::string& function,
			       const std::string& file,
			       int line,
			       const std::vector<std::string>& messages)
{
  std::ostringstream alert;
  alert << "* " << title << " - " << function << " (" << file << ":" << line << ")" << std::endl;
  for (const std::string& message : messages)
    alert << "  " << message << std::endl;
  return alert.str();
}
