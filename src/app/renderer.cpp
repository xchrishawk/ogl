/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "app/renderer.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "opengl/vertex_array.hpp"
#include "shaders/shader_sources.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const GLuint BINDING_INDEX = 0;
}

/* -- Procedures -- */

renderer::renderer()
  : m_vao()
{
  m_vao = vertex_array::create();
  m_program = init_program();

  GLint position_attribute = m_program->attribute_location("vs_position");
  ogl_assert(position_attribute != -1);
  m_vao->vertex_buffer_format(BINDING_INDEX, position_attribute, vertex_position::COUNT, offsetof(vertex, position));

  GLint color_attribute = m_program->attribute_location("vs_color");
  ogl_assert(color_attribute != -1);
  m_vao->vertex_buffer_format(BINDING_INDEX, color_attribute, vertex_color::COUNT, offsetof(vertex, color));
}

renderer::~renderer()
{
}

void renderer::render(float abs_t, float delta_t)
{
  clear_buffer();

  m_program->activate();
  m_vao->activate();

  vertex_array::unactivate();
  program::unactivate();
}

program::ptr renderer::init_program()
{
  shader::ptr vertex_shader = shader::create(GL_VERTEX_SHADER);
  vertex_shader->set_source(DEFAULT_VERTEX_SHADER_SOURCE);
  vertex_shader->compile();

  shader::ptr fragment_shader = shader::create(GL_FRAGMENT_SHADER);
  fragment_shader->set_source(DEFAULT_FRAGMENT_SHADER_SOURCE);
  fragment_shader->compile();

  program::ptr program = program::create();
  program->attach_shader(vertex_shader);
  program->attach_shader(fragment_shader);
  program->link();

  program->detach_shader(vertex_shader);
  program->detach_shader(fragment_shader);

  return program;
}

void renderer::clear_buffer()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
