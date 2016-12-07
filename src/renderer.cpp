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
#include "vertex_array.hpp"

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
  loop_init(width, height);

  // view matrix
  glm::mat4 view =
    glm::translate(state.camera_pos()) *				// translation (done second)
    glm::mat4_cast(state.camera_rot());					// rotation (done first)
  view = glm::inverse(view);						// invert origin->camera into camera->origin

  // create projection matrix
  glm::mat4 proj = glm::perspective(state.camera_fov(),			// field of view (Y axis)
				    (float)width / (float)height,	// aspect ratio
				    0.1f,				// near clip
				    100.0f);				// far clip

  m_program->activate();

  for (mesh::const_ptr mesh : state.meshes())
  {
    // create MVP matrix for this mesh
    glm::mat4 model;
    glm::mat4 mvp = proj * view * model;

    // draw elements in this mesh
    mesh->vertex_array()->bind();
    glUniformMatrix4fv(TRANSFORM_UNIFORM_LOCATION, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, mesh->index_count(), GL_UNSIGNED_INT, NULL);
    vertex_array::unbind();
  }

  program::unactivate();
}

void renderer::loop_init(int width, int height)
{
  // set aspect ratio
  glViewport(0, 0, width, height);

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // clear the color and depth buffers
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
