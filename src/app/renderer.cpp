/**
 * @file	renderer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include "app/renderer.hpp"
#include "app/state.hpp"
#include "app/vertex.hpp"
#include "opengl/api.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "shaders/shader_manager.hpp"
#include "util/constants.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const GLuint VERTEX_BUFFER_BINDING = 0;
}

/* -- Procedures -- */

renderer::renderer()
  : m_program(renderer::init_program()),
    m_vao(renderer::init_vao(m_program)),
    m_buffer(renderer::init_buffer())
{
  // one-time initial setup - TEMPORARILY DISABLED
  // enable_depth_testing();
  // enable_face_culling();
}

renderer::~renderer()
{
}

void renderer::render(const render_args& args)
{
  clear_buffer(args);

  // TEMP
  program::use(m_program);
  vertex_array::bind(m_vao);
  m_vao->bind_vertex_buffer(VERTEX_BUFFER_BINDING, m_buffer, sizeof(vertex), 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  m_vao->unbind_vertex_buffer(VERTEX_BUFFER_BINDING);
  vertex_array::bind_none();
  program::use_none();
}

program::ptr renderer::init_program()
{
  shader::ptr vertex_shader = shader::create(GL_VERTEX_SHADER);
  vertex_shader->set_source(shaders::VERTEX_SHADER_SOURCE);
  vertex_shader->compile();

  shader::ptr fragment_shader = shader::create(GL_FRAGMENT_SHADER);
  fragment_shader->set_source(shaders::FRAGMENT_SHADER_SOURCE);
  fragment_shader->compile();

  program::ptr program = program::create();
  program->link({ vertex_shader, fragment_shader });

  return program;
}

vertex_array::ptr renderer::init_vao(const program::const_ptr& program)
{
  vertex_array::ptr vao = vertex_array::create();

  // vertex position attribute
  GLint position_attribute = program->attribute_location("vertex_position");
  if (position_attribute != constants::OPENGL_INVALID_LOCATION)
  {
    vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			      position_attribute,
			      vertex_position::COUNT,
			      offsetof(vertex, position));
  }
  else
  {
    ogl_debug_print("Warning: Did not find attribute location for vertex_position");
  }

  // vertex normal attribute
  GLint normal_attribute = program->attribute_location("vertex_normal");
  if (normal_attribute != constants::OPENGL_INVALID_LOCATION)
  {
    vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			      normal_attribute,
			      vertex_normal::COUNT,
			      offsetof(vertex, color));
  }
  else
  {
    ogl_debug_print("Warning: Did not find attribute location for vertex_normal");
  }

  // vertex color attribute
  GLint color_attribute = program->attribute_location("vertex_color");
  if (color_attribute != constants::OPENGL_INVALID_LOCATION)
  {
    vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			      color_attribute,
			      vertex_color::COUNT,
			      offsetof(vertex, color));
  }
  else
  {
    ogl_debug_print("Warning: Did not find attribute location for vertex_color");
  }

  // vertex texture coordinates attribute
  GLint texture_attribute = program->attribute_location("vertex_texture");
  if (texture_attribute != constants::OPENGL_INVALID_LOCATION)
  {
    vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			      texture_attribute,
			      vertex_texture::COUNT,
			      offsetof(vertex, texture));
  }
  else
  {
    ogl_debug_print("Warning: Did not find attribute location for vertex_texture");
  }

  return vao;
}

buffer::ptr renderer::init_buffer()
{
  static const vertex vertices[] = {
    { { 0.0f, 0.0f, 0.0f }, { }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { { 0.0f, 0.5f, 0.0f }, { }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.5f, 0.0f, 0.0f }, { }, { 0.0f, 0.0f, 1.0f, 1.0f } },
  };
  return immutable_buffer::create(sizeof(vertices), vertices, 0);
}

void renderer::enable_depth_testing()
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void renderer::enable_face_culling()
{
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
}

void renderer::clear_buffer(const render_args& args)
{
  // update viewport dimensions
  glViewport(0, 0, args.framebuffer_width, args.framebuffer_height);

  // clear buffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
