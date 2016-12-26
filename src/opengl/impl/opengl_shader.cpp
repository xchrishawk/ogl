/**
 * @file	opengl_shader.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

#include "opengl/shader.hpp"
#include "opengl/impl/opengl_shader.hpp"

/* -- Namespaces -- */

using namespace ogl;
using namespace ogl::impl;

/* -- Procedures -- */

shader::ptr opengl_shader::create(shader_type type)
{
  return shader::ptr(new opengl_shader(type));
}

opengl_shader::opengl_shader(shader_type type)
  : shader(type)
{
}

opengl_shader::~opengl_shader()
{
}
