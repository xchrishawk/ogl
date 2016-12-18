/**
 * @file	buffer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <memory>

#include "opengl/api.hpp"
#include "opengl/buffer.hpp"
#include "opengl/error.hpp"
#include "opengl/exceptions.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

buffer::buffer()
  : m_handle(buffer::new_handle())
{
}

buffer::~buffer()
{
  glDeleteBuffers(1, &m_handle);
}

GLuint buffer::new_handle()
{
  GLuint handle = 0;
  glCreateBuffers(1, &handle);
  if (handle == 0)
    throw alloc_exception("Failed to create buffer!");
  return handle;
}

immutable_buffer::ptr immutable_buffer::create(GLsizei size, const void* data, GLbitfield flags)
{
  return immutable_buffer::ptr(new immutable_buffer(size, data, flags));
}

immutable_buffer::immutable_buffer(GLsizei size, const void* data, GLbitfield flags)
  : buffer()
{
  glNamedBufferStorage(handle(), size, data, flags);
}
