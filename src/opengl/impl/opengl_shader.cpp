/**
 * @file	opengl_shader.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>
#include <vector>

#include <GL/glew.h>

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
  /** Creates and returns a new shader handle. */
  GLuint new_shader_handle(shader_type type);

  /** Convert an `ogl::shader_type` to a `GLenum`. */
  GLenum shader_type_to_enum(shader_type type);

  /** Convert an `ogl::shader_type` to a `std::string`. */
  std::string shader_type_to_string(shader_type type);
}

/* -- Procedures -- */

shader::ptr opengl_shader::create(shader_type type)
{
  return shader::ptr(new opengl_shader(type));
}

opengl_shader::opengl_shader(shader_type type)
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
  GLuint new_shader_handle(shader_type type)
  {
    GLenum type_enum = shader_type_to_enum(type);
    GLuint handle = glCreateShader(type_enum);
    if (handle == INVALID_SHADER_HANDLE)
      throw opengl_exception("Failed to create shader of type " + shader_type_to_string(type));
    return handle;
  }

  GLenum shader_type_to_enum(shader_type type)
  {
    switch (type)
    {
    case shader_type::compute_shader:		return GL_COMPUTE_SHADER;
    case shader_type::vertex_shader:		return GL_VERTEX_SHADER;
    case shader_type::tess_control_shader:	return GL_TESS_CONTROL_SHADER;
    case shader_type::tess_evaluation_shader:	return GL_TESS_EVALUATION_SHADER;
    case shader_type::geometry_shader:		return GL_GEOMETRY_SHADER;
    case shader_type::fragment_shader:		return GL_FRAGMENT_SHADER;
    default:
      ogl_dbg_assert_fail("Invalid shader type!");
      return 0;
    }
  }

  std::string shader_type_to_string(shader_type type)
  {
    switch (type)
    {
    case shader_type::compute_shader:		return "GL_COMPUTE_SHADER";
    case shader_type::vertex_shader:		return "GL_VERTEX_SHADER";
    case shader_type::tess_control_shader:	return "GL_TESS_CONTROL_SHADER";
    case shader_type::tess_evaluation_shader:	return "GL_TESS_EVALUATION_SHADER";
    case shader_type::geometry_shader:		return "GL_GEOMETRY_SHADER";
    case shader_type::fragment_shader:		return "GL_FRAGMENT_SHADER";
    default:
      ogl_dbg_assert_fail("Invalid shader type!");
      return "Unknown";
    }
  }
}
