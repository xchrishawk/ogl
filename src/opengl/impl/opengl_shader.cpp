/**
 * @file	opengl_shader.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>
#include <vector>

#include "opengl/api.hpp"
#include "opengl/opengl.hpp"
#include "opengl/shader.hpp"
#include "opengl/impl/opengl_shader.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;
using namespace ogl::impl;

/* -- Constants -- */

namespace
{
  const GLuint INVALID_SHADER_HANDLE = 0;
}

/* -- Procedure Prototypes -- */

namespace
{
  GLuint new_shader_handle(GLenum type);
  std::string shader_type_to_string(GLenum type);
}

/* -- Procedures -- */

shader::ptr opengl_shader::create(GLenum type)
{
  return shader::ptr(new opengl_shader(type));
}

opengl_shader::opengl_shader(GLenum type)
  : shader(type),
    m_handle(new_shader_handle(type))
{
  if (m_handle == INVALID_SHADER_HANDLE)
    throw opengl_exception("Failed to create shader!");
}

opengl_shader::~opengl_shader()
{
  glDeleteShader(m_handle);
}

void opengl_shader::set_source(const std::string& source)
{
  const char* source_str = source.c_str();
  glShaderSource(m_handle, 1, &source_str, NULL);
}

void opengl_shader::compile()
{
  glCompileShader(m_handle);
  if (!is_compiled())
  {
    std::ostringstream message;
    message << "Failed to compile shader of type " << shader_type_to_string(type()) << std::endl;
    message << info_log();
    throw opengl_exception(message.str());
  }
}

bool opengl_shader::is_compiled() const
{
  GLint is_compiled = GL_FALSE;
  glGetShaderiv(m_handle, GL_COMPILE_STATUS, &is_compiled);
  return (is_compiled == GL_TRUE);
}

std::string opengl_shader::info_log() const
{
  GLint info_log_length = 0;
  glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length == 0)
    return "";

  std::vector<char> info_log_buffer(info_log_length);
  glGetShaderInfoLog(m_handle, info_log_length, NULL, info_log_buffer.data());
  std::string info_log(info_log_buffer.begin(), info_log_buffer.end());

  return info_log;
}

/* -- Private Procedures -- */

namespace
{
  GLuint new_shader_handle(GLenum type)
  {
    GLuint handle = glCreateShader(type);
    if (handle == INVALID_SHADER_HANDLE)
      throw opengl_exception("Failed to create shader of type " + shader_type_to_string(type));
    return handle;
  }

  std::string shader_type_to_string(GLenum type)
  {
    switch (type)
    {
    case GL_COMPUTE_SHADER:		return "GL_COMPUTE_SHADER";
    case GL_VERTEX_SHADER:		return "GL_VERTEX_SHADER";
    case GL_TESS_CONTROL_SHADER:	return "GL_TESS_CONTROL_SHADER";
    case GL_TESS_EVALUATION_SHADER:	return "GL_TESS_EVALUATION_SHADER";
    case GL_GEOMETRY_SHADER:		return "GL_GEOMETRY_SHADER";
    case GL_FRAGMENT_SHADER:		return "GL_FRAGMENT_SHADER";
    default:
      ogl_dbg_assert_fail("Invalid shader type!");
      return "Unknown";
    }
  }
}
