/**
 * buffer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>
#include <sstream>
#include <string>

#include <GL/glew.h>

#include "opengl/buffer.hpp"
#include "opengl/error.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

buffer::buffer()
{
  glCreateBuffers(1, &m_id);
  if (m_id == 0)
  {
    GLenum error = opengl_last_error();
    ostringstream message;
    message << "Failed to create buffer. " << opengl_error_string(error);
    throw runtime_error(message.str());
  }
}

buffer::~buffer()
{
  glDeleteBuffers(1, &m_id);
}

immutable_buffer::ptr immutable_buffer::create(GLsizei size, const void* data, GLbitfield flags)
{
  return immutable_buffer::ptr(new immutable_buffer(size, data, flags));
}

immutable_buffer::immutable_buffer(GLsizei size, const void* data, GLbitfield flags)
  : buffer()
{
  glNamedBufferStorage(*this, size, data, flags);
}
