/**
 * glew.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>

#include "glew.hpp"
#include "opengl.hpp"
#include "util.hpp"

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

  glew::initialized = true;
}

glew::~glew()
{
  glew::initialized = false;
}
