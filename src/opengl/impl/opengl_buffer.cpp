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

/* -- Private Procedures -- */

namespace
{
  GLuint new_buffer_handle()
  {
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    return buffer;
  }
}
