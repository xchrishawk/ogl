/**
 * glew.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>

#include "opengl/error.hpp"
#include "opengl/glew.hpp"
#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Variables -- */

bool glew::initialized = false;

/* -- Procedures -- */

glew::glew(bool experimental)
{
  ogl_assert(!glew::initialized);

  glewExperimental = (experimental ? GL_TRUE : GL_FALSE);
  GLenum error = glewInit();
  if (error != GLEW_OK)
    throw runtime_error("Failed to initialize GLEW");

  // glewInit() causes an OpenGL error to get queued, so flush it out
  __attribute__((unused)) GLenum spurious_error = opengl_last_error();

  glew::initialized = true;
}

glew::~glew()
{
  glew::initialized = false;
}
