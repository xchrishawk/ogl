/**
 * shader.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include <GL/glew.h>

#include "opengl/error.hpp"
#include "opengl/shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

shader::ptr shader::create(GLenum type)
{
  return shader::ptr(new shader(type));
}

shader::shader(GLenum type)
  : m_type(type),
    m_handle(glCreateShader(m_type))
{
  if (m_handle == 0)
    opengl_throw_last_error("Failed to create shader.");
}

shader::~shader()
{
  glDeleteShader(m_handle);
}

void shader::set_source(const string& source)
{
  const char* source_ptr = source.c_str();
  glShaderSource(m_handle, 1, &source_ptr, NULL);
}

void shader::load_source(const string& filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    ostringstream message;
    message << "Could not open " << filename << ".";
    throw runtime_error(message.str());
  }

  stringstream buffer;
  buffer << file.rdbuf();
  set_source(buffer.str());
}

void shader::compile()
{
  glCompileShader(m_handle);
  if (!is_compiled())
  {
    ostringstream message;
    message << "Failed to compile shader." << endl << info_log();
    throw runtime_error(message.str());
  }
}

bool shader::is_compiled() const
{
  GLint is_compiled = GL_FALSE;
  glGetShaderiv(m_handle, GL_COMPILE_STATUS, &is_compiled);
  return (is_compiled == GL_TRUE);
}

string shader::info_log() const
{
  GLint info_log_length = 0;
  glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return string();

  char* info_log_buffer = new char[info_log_length];
  glGetShaderInfoLog(m_handle, info_log_length, NULL, info_log_buffer);
  string info_log(info_log_buffer);
  delete[] info_log_buffer;

  return info_log;
}
