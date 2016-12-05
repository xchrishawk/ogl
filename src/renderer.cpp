/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl.hpp"
#include "program.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "shader_source.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const size_t VERTEX_COUNT = 6;
  const GLuint BINDING_INDEX = 0;
  const GLuint POSITION_ATTRIBUTE_INDEX = 0;
  const GLuint COLOR_ATTRIBUTE_INDEX = 1;
}

/* -- Procedures -- */

renderer::renderer()
{
  auto vertex_shader = shader::create(GL_VERTEX_SHADER);
  vertex_shader->set_source(VERTEX_SHADER_SOURCE);
  vertex_shader->compile();

  auto fragment_shader = shader::create(GL_FRAGMENT_SHADER);
  fragment_shader->set_source(FRAGMENT_SHADER_SOURCE);
  fragment_shader->compile();

  m_program = program::create();
  m_program->attach_shaders({ vertex_shader, fragment_shader });
  m_program->link();
  m_program->detach_shaders({ vertex_shader, fragment_shader });
}

renderer::~renderer()
{
}

void renderer::loop(const state& state)
{
  clear();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GREATER);

  glUseProgram(m_program->id());

  for (mesh::const_ptr mesh : state.meshes())
  {
    glBindVertexArray(mesh->vertex_array());
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count());
    glBindVertexArray(0);
  }

  glUseProgram(0);
}

void renderer::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
