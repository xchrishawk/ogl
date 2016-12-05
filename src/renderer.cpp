/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include "constants.hpp"
#include "opengl.hpp"
#include "program.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "shader_source.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace ogl;

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

void renderer::loop(int width, int height, const state& state)
{
  glViewport(0, 0, width, height);
  clear();

  glUseProgram(m_program->id());

  for (mesh::const_ptr mesh : state.meshes())
  {
    glBindVertexArray(mesh->vertex_array());

    glm::mat4 view;
    view = glm::translate(view, state.camera_pos());
    view = glm::rotate(view, state.camera_rot().x, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, state.camera_rot().y, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, state.camera_rot().z, glm::vec3(0.0f, 0.0f, 1.0f));
    view = glm::inverse(view);

    glm::mat4 proj = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 mvp = proj * view;
    glUniformMatrix4fv(TRANSFORM_UNIFORM_LOCATION, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawElements(GL_TRIANGLES, mesh->index_count(), GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
  }

  glUseProgram(0);
}

void renderer::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
