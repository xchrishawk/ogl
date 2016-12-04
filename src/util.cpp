/**
 * util.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

#include "util.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
#ifdef OGL_DEBUG
  ostream& LOG_STREAM = cout;
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
  std::raise(SIGINT);
  exit(EXIT_FAILURE);
}

void ogl::_ogl_trace(const string& func, const string& file, int line, const string& message)
{
  LOG_STREAM << "ogl_trace - " << func << " (" << file << ":" << line << ")";
  if (message.length() != 0)
    LOG_STREAM << " - " << message;
  LOG_STREAM << endl;
}

#endif
