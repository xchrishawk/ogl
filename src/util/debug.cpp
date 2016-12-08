/**
 * debug.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
#ifdef OGL_DEBUG
  ostream& TRACE_STREAM = cout;
  ostream& ERROR_STREAM = cerr;
#endif
}

/* -- Procedures -- */

#ifdef OGL_DEBUG

void ogl::_ogl_fail(const string& func, const string& file, int line, const string& message)
{
  ERROR_STREAM << endl
	       << "*** ogl_fail - " << func << " (" << file << ":" << line << ")" << endl
	       << "    " << message << endl
	       << endl;
  ogl_break();
  exit(EXIT_FAILURE);
}

void ogl::_ogl_trace(const string& func, const string& file, int line, const string& message)
{
  TRACE_STREAM << "* ogl_trace - " << func << " (" << file << ":" << line << ")" << endl;
  if (message.length() != 0)
    TRACE_STREAM << "  " << message << endl;
}

void ogl::_ogl_error(const string& func, const string& file, int line, const string& message)
{
  ERROR_STREAM << "* ogl_error - " << func << " (" << file << ":" << line << ")" << endl;
  if (message.length() != 0)
    ERROR_STREAM << "  " << message << endl;
}

void ogl::_ogl_break()
{
  std::raise(SIGINT);
}

#endif
