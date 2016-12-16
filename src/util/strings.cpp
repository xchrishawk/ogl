/**
 * @file	strings.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cstdarg>
#include <cstdlib>
#include <string>

#include "util/strings.hpp"

/* -- Procedures -- */

std::string ogl::stringf(const std::string& format, ...)
{
  va_list args;
  va_start(args, format);

  char* buffer = nullptr;
  int result = vasprintf(&buffer, format.c_str(), args);

  va_end(args);

  if (result >= 0)
  {
    std::string ret(buffer);
    free(buffer);
    return ret;
  }
  else
  {
    // failed to allocate memory
    return "";
  }
}
