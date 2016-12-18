/**
 * @file	program.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "opengl/error.hpp"
#include "opengl/exceptions.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

program::ptr program::create()
{
  return program::ptr(new program());
}

void program::deactivate()
{
  glUseProgram(0);
}

program::program()
  : m_handle(program::new_handle())
{
}

program::~program()
{
  glDeleteProgram(m_handle);
}

void program::attach_shader(shader::const_ptr shader)
{
  glAttachShader(m_handle, shader->handle());
}

void program::detach_shader(shader::const_ptr shader)
{
  glDetachShader(m_handle, shader->handle());
}

void program::link()
{
  glLinkProgram(m_handle);
  if (!is_linked())
  {
    std::ostringstream message;
    message << "Failed to link program." << std::endl << info_log();
    throw shader_exception(message.str());
  }
}

void program::activate() const
{
  glUseProgram(m_handle);
}

bool program::is_linked() const
{
  GLint is_linked = GL_FALSE;
  glGetProgramiv(m_handle, GL_LINK_STATUS, &is_linked);
  return (is_linked == GL_TRUE);
}

std::string program::info_log() const
{
  GLint info_log_length = 0;
  glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return "";

  std::shared_ptr<char> info_log_buffer(new char[info_log_length]);
  glGetProgramInfoLog(m_handle, info_log_length, NULL, info_log_buffer.get());
  std::string info_log(info_log_buffer.get());

  return info_log;
}

GLint program::attribute_location(const std::string& name)
{
  return glGetAttribLocation(m_handle, name.c_str());
}

GLint program::uniform_location(const std::string& name)
{
  return glGetUniformLocation(m_handle, name.c_str());
}

GLuint program::new_handle()
{
  GLuint handle = glCreateProgram();
  if (handle == 0)
    throw alloc_exception("Failed to create shader program!");
  return handle;
}
