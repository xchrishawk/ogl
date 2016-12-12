/**
 * texture.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <memory>

#include <GL/glew.h>

#include "opengl/error.hpp"
#include "opengl/texture.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

texture::texture(GLenum target)
  : m_target(target),
    m_handle(texture::new_handle(target))
{
}

texture::~texture()
{
  glDeleteTextures(1, &m_handle);
}

GLuint texture::new_handle(GLenum target)
{
  GLuint handle = 0;
  glCreateTextures(target, 1, &handle);
  if (handle == 0)
    opengl_throw_last_error("Failed to create texture.");
  return handle;
}

texture2d::ptr texture2d::create(GLsizei levels,
				 GLenum internal_format,
				 GLsizei width,
				 GLsizei height)
{
  return texture2d::ptr(new texture2d(levels, internal_format, width, height));
}

texture2d::texture2d(GLsizei levels,
		     GLenum internal_format,
		     GLsizei width,
		     GLsizei height)
  : texture(GL_TEXTURE_2D),
    m_levels(levels),
    m_internal_format(internal_format),
    m_width(width),
    m_height(height)
{
  glTextureStorage2D(handle(),			// texture
		     m_levels,			// levels
		     m_internal_format,		// internalformat
		     m_width,			// width
		     m_height);			// height
}

void texture2d::set_image(GLint level,
			  GLint x_offset,
			  GLint y_offset,
			  GLsizei width,
			  GLsizei height,
			  GLenum format,
			  GLenum type,
			  const void* pixels)
{
  glTextureSubImage2D(handle(),			// texture
		      level,			// level
		      x_offset,			// xoffset
		      y_offset,			// yoffset
		      width,			// width
		      height,			// height
		      format,			// format
		      type,			// type
		      pixels);			// pixels
}
