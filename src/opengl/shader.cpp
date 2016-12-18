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

#include "opengl/api.hpp"
#include "opengl/error.hpp"
#include "opengl/exceptions.hpp"
#include "opengl/shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

shader::ptr shader::create(GLenum type)
{
  return shader::ptr(new shader(type));
}

shader::shader(GLenum type)
  : m_type(type),
    m_handle(shader::new_handle(type))
{
}

shader::~shader()
{
  glDeleteShader(m_handle);
}

void shader::set_source(const std::string& source)
{
  const char* source_ptr = source.c_str();
  glShaderSource(m_handle, 1, &source_ptr, NULL);
}

void shader::load_source(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::ostringstream message;
    message << "Unable to open shader source file " << filename << ".";
    throw file_io_exception(message.str());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  set_source(buffer.str());
}

void shader::compile()
{
  glCompileShader(m_handle);
  if (!is_compiled())
  {
    std::ostringstream message;
    message << "Failed to compile shader of type " << shader_type_name(m_type) << std::endl;
    message << info_log();
    throw shader_exception(message.str());
  }
}

bool shader::is_compiled() const
{
  GLint is_compiled = GL_FALSE;
  glGetShaderiv(m_handle, GL_COMPILE_STATUS, &is_compiled);
  return (is_compiled == GL_TRUE);
}

std::string shader::info_log() const
{
  GLint info_log_length = 0;
  glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return "";

  std::shared_ptr<char> info_log_buffer(new char[info_log_length]);
  glGetShaderInfoLog(m_handle, info_log_length, NULL, info_log_buffer.get());
  std::string info_log(info_log_buffer.get());

  return info_log;
}

GLuint shader::new_handle(GLenum type)
{
  GLuint handle = glCreateShader(type);
  if (handle == 0)
  {
    std::ostringstream message;
    message << "Failed to create shader of type " << shader_type_name(type) << "!";
    throw ogl::alloc_exception(message.str());
  }

  return handle;
}

std::string shader::shader_type_name(GLenum type)
{
  switch (type)
  {
  case GL_COMPUTE_SHADER:
    return "GL_COMPUTE_SHADER";
  case GL_FRAGMENT_SHADER:
    return "GL_FRAGMENT_SHADER";
  case GL_GEOMETRY_SHADER:
    return "GL_GEOMETRY_SHADER";
  case GL_TESS_CONTROL_SHADER:
    return "GL_TESS_CONTROL_SHADER";
  case GL_TESS_EVALUATION_SHADER:
    return "GL_TESS_EVALUATION_SHADER";
  case GL_VERTEX_SHADER:
    return "GL_VERTEX_SHADER";
  default:
    ogl_assert_fail("Unknown shader type!");
    return "Unknown";
  }
}
