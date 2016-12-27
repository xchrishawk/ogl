/**
 * @file	opengl_buffer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

/* -- Includes -- */

#include <GL/glew.h>

#include "opengl/buffer.hpp"
#include "opengl/opengl.hpp"
#include "opengl/impl/opengl_buffer.hpp"
#include "util/cleanup.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;
using namespace ogl::impl;

/* -- Procedure Prototypes -- */

namespace
{
  GLuint new_buffer_handle();
  GLenum buffer_type_to_enum(buffer_type type);
  GLenum buffer_usage_to_enum(buffer_usage usage);
  GLbitfield buffer_flags_to_bitfield(buffer_flags flags);
}

/* -- Procedures -- */

opengl_buffer::opengl_buffer()
  : buffer(),
    m_handle(new_buffer_handle())
{
}

opengl_buffer::~opengl_buffer()
{
  glDeleteBuffers(1, &m_handle);
}

buffer::ptr opengl_immutable_buffer::create(buffer_type type,
					    const void* data,
					    size_t size,
					    buffer_flags flags)
{
  return buffer::ptr(new opengl_immutable_buffer(type, data, size, flags));
}

opengl_immutable_buffer::opengl_immutable_buffer(buffer_type type,
						 const void* data,
						 size_t size,
						 buffer_flags flags)
{
  GLenum type_enum = buffer_type_to_enum(type);
  GLuint current_buffer = glGet(
}

/* -- Private Procedures -- */

namespace
{
  GLuint new_buffer_handle()
  {
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    return buffer;
  }

  GLenum buffer_type_to_enum(buffer_type type)
  {
    switch (type)
    {
    case buffer_type::array_buffer:			return GL_ARRAY_BUFFER;
    case buffer_type::atomic_counter_buffer:		return GL_ATOMIC_COUNTER_BUFFER;
    case buffer_type::copy_read_buffer:			return GL_COPY_READ_BUFFER;
    case buffer_type::copy_write_buffer:		return GL_COPY_WRITE_BUFFER;
    case buffer_type::dispatch_indirect_buffer:		return GL_DISPATCH_INDIRECT_BUFFER;
    case buffer_type::draw_indirect_buffer:		return GL_DRAW_INDIRECT_BUFFER;
    case buffer_type::element_array_buffer:		return GL_ELEMENT_ARRAY_BUFFER;
    case buffer_type::pixel_pack_buffer:		return GL_PIXEL_PACK_BUFFER;
    case buffer_type::pixel_unpack_buffer:		return GL_PIXEL_UNPACK_BUFFER;
    case buffer_type::query_buffer:			return GL_QUERY_BUFFER;
    case buffer_type::shader_storage_buffer:		return GL_SHADER_STORAGE_BUFFER;
    case buffer_type::texture_buffer:			return GL_TEXTURE_BUFFER;
    case buffer_type::transform_feedback_buffer:	return GL_TRANSFORM_FEEDBACK_BUFFER;
    case buffer_type::uniform_buffer:			return GL_UNIFORM_BUFFER;
    default:
      ogl_dbg_assert_fail("Unknown buffer type!");
      return 0;
    }
  }

  GLenum buffer_type_to_binding_enum(buffer_type type)
  {
    switch (type)
    {
    case buffer_type::array_buffer:			return GL_ARRAY_BUFFER_BINDING;
    case buffer_type::atomic_counter_buffer:		return GL_ATOMIC_COUNTER_BUFFER;
    case buffer_type::copy_read_buffer:			return GL_COPY_READ_BUFFER;
    case buffer_type::copy_write_buffer:		return GL_COPY_WRITE_BUFFER;
    case buffer_type::dispatch_indirect_buffer:		return GL_DISPATCH_INDIRECT_BUFFER;
    case buffer_type::draw_indirect_buffer:		return GL_DRAW_INDIRECT_BUFFER;
    case buffer_type::element_array_buffer:		return GL_ELEMENT_ARRAY_BUFFER;
    case buffer_type::pixel_pack_buffer:		return GL_PIXEL_PACK_BUFFER;
    case buffer_type::pixel_unpack_buffer:		return GL_PIXEL_UNPACK_BUFFER;
    case buffer_type::query_buffer:			return GL_QUERY_BUFFER;
    case buffer_type::shader_storage_buffer:		return GL_SHADER_STORAGE_BUFFER;
    case buffer_type::texture_buffer:			return GL_TEXTURE_BUFFER;
    case buffer_type::transform_feedback_buffer:	return GL_TRANSFORM_FEEDBACK_BUFFER;
    case buffer_type::uniform_buffer:			return GL_UNIFORM_BUFFER;
    default:
      ogl_dbg_assert_fail("Unknown buffer type!");
      return 0;
    }
  }

  GLenum buffer_usage_to_enum(buffer_usage usage)
  {
    switch (usage)
    {
    case buffer_usage::stream_draw:			return GL_STREAM_DRAW;
    case buffer_usage::stream_read:			return GL_STREAM_READ;
    case buffer_usage::stream_copy:			return GL_STREAM_COPY;
    case buffer_usage::static_draw:			return GL_STATIC_DRAW;
    case buffer_usage::static_read:			return GL_STATIC_READ;
    case buffer_usage::static_copy:			return GL_STATIC_COPY;
    case buffer_usage::dynamic_draw:			return GL_DYNAMIC_DRAW;
    case buffer_usage::dynamic_read:			return GL_DYNAMIC_READ;
    case buffer_usage::dynamic_copy:			return GL_DYNAMIC_COPY;
    default:
      ogl_dbg_assert_fail("Unknown buffer usage!");
      return 0;
    }
  }

  GLbitfield buffer_flags_to_bitfield(buffer_flags flags)
  {
    GLbitfield bitfield = 0;

    auto check = [&] (buffer_flags bufferflag, GLbitfield glbit) {
      if (flags & bufferflag)
      {
	bitfield |= glbit;
	flags = static_cast<buffer_flags>(static_cast<int>(flags) & static_cast<int>(~bufferflag));
      }
    };

    check(BUFFER_FLAGS_DYNAMIC_STORAGE, GL_DYNAMIC_STORAGE_BIT);
    check(BUFFER_FLAGS_MAP_READ, 	GL_MAP_READ_BIT);
    check(BUFFER_FLAGS_MAP_WRITE, 	GL_MAP_WRITE_BIT);
    check(BUFFER_FLAGS_MAP_PERSISTENT, 	GL_MAP_PERSISTENT_BIT);
    check(BUFFER_FLAGS_MAP_COHERENT, 	GL_MAP_COHERENT_BIT);
    check(BUFFER_FLAGS_CLIENT_STORAGE,	GL_CLIENT_STORAGE_BIT);

    // make sure we didn't miss any flags
    ogl_dbg_assert(flags == BUFFER_FLAGS_NONE);
    return bitfield;
  }
}
