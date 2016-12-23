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
#include "util/debug.hpp"
#include "util/exceptions.hpp"

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

void* buffer::map(GLenum access)
{
  return glMapNamedBuffer(m_handle, access);
}

void* buffer::map_range(GLintptr offset, GLsizei length, GLbitfield access)
{
  return glMapNamedBufferRange(m_handle, offset, length, access);
}

void buffer::sub_data(GLintptr offset, GLsizei size, const void* data)
{
  glNamedBufferSubData(m_handle, offset, size, data);
}

bool buffer::is_immutable() const
{
  GLint immutable = 0;
  glGetNamedBufferParameteriv(m_handle, GL_BUFFER_IMMUTABLE_STORAGE, &immutable);
  return GLint_to_bool(immutable);
}

bool buffer::is_mapped() const
{
  GLint mapped = 0;
  glGetNamedBufferParameteriv(m_handle, GL_BUFFER_MAPPED, &mapped);
  return GLint_to_bool(mapped);
}

GLint64 buffer::map_length() const
{
  GLint64 map_length = 0;
  glGetNamedBufferParameteri64v(m_handle, GL_BUFFER_MAP_LENGTH, &map_length);
  return map_length;
}

GLint64 buffer::map_offset() const
{
  GLint64 map_offset = 0;
  glGetNamedBufferParameteri64v(m_handle, GL_BUFFER_MAP_OFFSET, &map_offset);
  return map_offset;
}

GLint buffer::size() const
{
  GLint size = 0;
  glGetNamedBufferParameteriv(m_handle, GL_BUFFER_SIZE, &size);
  return size;
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
