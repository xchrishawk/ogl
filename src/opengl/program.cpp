/**
 * program.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "opengl/error.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

program::ptr program::create()
{
  return program::ptr(new program());
}

void program::unactivate()
{
  glUseProgram(0);
}

program::program()
  : m_handle(glCreateProgram())
{
  if (m_handle == 0)
    opengl_throw_last_error("Failed to create program.");
}

program::~program()
{
  glDeleteProgram(m_handle);
}

void program::attach_shader(shader::const_ptr shader)
{
  glAttachShader(m_handle, shader->handle());
}

void program::attach_shaders(const vector<shader::const_ptr>& shaders)
{
  for (shader::const_ptr shader : shaders)
    attach_shader(shader);
}

void program::detach_shader(shader::const_ptr shader)
{
  glDetachShader(m_handle, shader->handle());
}

void program::detach_shaders(const vector<shader::const_ptr>& shaders)
{
  for (shader::const_ptr shader : shaders)
    detach_shader(shader);
}

void program::link()
{
  glLinkProgram(m_handle);
  if (!is_linked())
  {
    ostringstream message;
    message << "Failed to link program." << endl << info_log();
    throw runtime_error(message.str());
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
    return string();

  char* info_log_buffer = new char[info_log_length];
  glGetProgramInfoLog(m_handle, info_log_length, NULL, info_log_buffer);
  string info_log(info_log_buffer);
  delete[] info_log_buffer;

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
