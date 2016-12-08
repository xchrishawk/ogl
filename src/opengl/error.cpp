/**
 * error.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <sstream>
#include <string>

#include <GL/glew.h>

#include "opengl/error.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

GLenum ogl::opengl_last_error()
{
  GLenum last_error = GL_NO_ERROR;

  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR)
  {
#ifdef OGL_DEBUG
    if (last_error != GL_NO_ERROR)
    {
      ostringstream message;
      message << "Ignoring " << opengl_error_string(last_error);
      ogl_error_message(message.str());
    }
#endif
    last_error = error;
  }

  return last_error;
}

string ogl::opengl_error_string(GLenum error)
{
  ostringstream string;
  string << "OpenGL error " << error << " (" << gluErrorString(error) << ")";
  return string.str();
}
