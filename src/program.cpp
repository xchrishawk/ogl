/**
 * program.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <memory>
#include <sstream>
#include <vector>

#include "opengl.hpp"
#include "program.hpp"
#include "util.hpp"

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
  {
    GLenum error = opengl_last_error();
    ostringstream message;
    message << "Failed to create program. " << opengl_error_string(error);
    throw runtime_error(message.str());
  }
}

program::~program()
{
  glDeleteProgram(m_id);
}

void program::attach_shader(shader::const_ptr shader)
{
  glAttachShader(m_id, shader->id());
}

void program::attach_shaders(const vector<shader::const_ptr>& shaders)
{
  for (shader::const_ptr shader : shaders)
    attach_shader(shader);
}

void program::detach_shader(shader::const_ptr shader)
{
  glDetachShader(m_id, shader->id());
}

void program::detach_shaders(const vector<shader::const_ptr>& shaders)
{
  for (shader::const_ptr shader : shaders)
    detach_shader(shader);
}

void program::link()
{
  glLinkProgram(m_id);
  if (!is_linked())
  {
    ostringstream message;
    message << "Failed to link program." << endl << info_log();
    throw runtime_error(message.str());
  }
}

bool program::is_linked() const
{
  GLint is_linked = GL_FALSE;
  glGetProgramiv(m_id, GL_LINK_STATUS, &is_linked);
  return (is_linked == GL_TRUE);
}

std::string program::info_log() const
{
  GLint info_log_length = 0;
  glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return string();

  char* info_log_buffer = new char[info_log_length];
  glGetProgramInfoLog(m_id, info_log_length, NULL, info_log_buffer);
  string info_log(info_log_buffer);
  delete[] info_log_buffer;

  return info_log;
}

GLint program::attribute_location(const std::string& name)
{
  return glGetAttribLocation(m_id, name.c_str());
}

GLint program::uniform_location(const std::string& name)
{
  return glGetUniformLocation(m_id, name.c_str());
}
