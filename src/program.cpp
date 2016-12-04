/**
 * program.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <memory>
#include <vector>

#include "opengl.hpp"
#include "program.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

program::ptr program::create()
{
  return program::ptr(new program());
}

program::program()
  : m_id(glCreateProgram())
{
  if (m_id == 0)
    opengl_throw_last_error("Failed to create program");
}

program::~program()
{
  glDeleteProgram(m_id);
}
