/**
 * @file	opengl_program.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "opengl/opengl.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "opengl/impl/opengl_program.hpp"
#include "opengl/impl/opengl_shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;
using namespace ogl::impl;

/* -- Constants -- */

namespace
{
  const GLuint INVALID_PROGRAM_HANDLE = 0;
}

/* -- Procedure Prototypes -- */

namespace
{
  /** Creates and returns a new program handle. */
  GLuint new_program_handle();

  /** Convert a `shader::const_ptr` to an `opengl_shader*`. */
  const opengl_shader* get_opengl_shader(const shader::const_ptr& ptr);
}

/* -- Procedures -- */

program::ptr opengl_program::create()
{
  return program::ptr(new opengl_program());
}

opengl_program::opengl_program()
  : program(),
    m_handle(new_program_handle())
{
}

opengl_program::~opengl_program()
{
  glDeleteProgram(m_handle);
}

void opengl_program::link(const std::vector<shader::const_ptr>& shaders)
{
  for (const auto& shader : shaders)
    glAttachShader(m_handle, get_opengl_shader(shader)->handle());

  glLinkProgram(m_handle);

  for (const auto& shader : shaders)
    glDetachShader(m_handle, get_opengl_shader(shader)->handle());

  if (!is_linked())
  {
    std::ostringstream message;
    message << "Failed to link program." << std::endl << info_log();
    throw opengl_exception(message.str());
  }
}

bool opengl_program::is_linked() const
{
  GLint is_linked = GL_FALSE;
  glGetProgramiv(m_handle, GL_LINK_STATUS, &is_linked);
  return (is_linked == GL_TRUE);
}

int opengl_program::attribute_count() const
{
  GLint active_attributes = 0;
  glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES, &active_attributes);
  return active_attributes;
}

int opengl_program::attribute_index(const std::string& name) const
{
  return glGetAttribLocation(m_handle, name.c_str());
}

int opengl_program::uniform_count() const
{
  GLint active_uniforms = 0;
  glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &active_uniforms);
  return active_uniforms;
}

int opengl_program::uniform_index(const std::string& name) const
{
  return glGetUniformLocation(m_handle, name.c_str());
}

std::string opengl_program::info_log() const
{
  GLint info_log_length;
  glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return "";

  std::vector<char> info_log_buffer(info_log_length);
  glGetProgramInfoLog(m_handle, info_log_length, NULL, info_log_buffer.data());
  std::string info_log(info_log_buffer.begin(), info_log_buffer.end());

  return info_log;
}

namespace
{
  GLuint new_program_handle()
  {
    GLuint handle = glCreateProgram();
    if (handle == INVALID_PROGRAM_HANDLE)
      throw opengl_exception("Failed to create program.");
    return handle;
  }

  const opengl_shader* get_opengl_shader(const shader::const_ptr& ptr)
  {
    const opengl_shader* shader = dynamic_cast<const opengl_shader*>(ptr.get());
    ogl_dbg_assert(shader != nullptr);
    return shader;
  }
}
