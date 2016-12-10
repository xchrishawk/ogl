/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "app/renderer.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "opengl/vertex_array.hpp"
#include "shaders/shader_sources.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace glm;
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

  m_meshes.push_back(example_meshes::rgb_triangle());
  m_meshes.push_back(example_meshes::cmy_triangle());
}

renderer::~renderer()
{
}

void renderer::render(int width, int height, const state& state)
{
  clear_buffer(width, height);

  // view matrix
  mat4 view =
    translate(state.camera_pos()) *			// translation (done second)
    mat4_cast(state.camera_rot());			// rotation (done first)
  view = inverse(view);					// invert origin->camera into camera->origin

  // create projection matrix
  mat4 proj = perspective(state.camera_fov(),		// field of view (Y axis)
			  (float)width / (float)height,	// aspect ratio
			  0.1f,				// near clip
			  100.0f);			// far clip

  m_program->activate();
  m_vao->activate();

  for (mesh m : m_meshes)
  {
    // create MVP matrix for this mesh
    glm::mat4 model;
    glm::mat4 mvp = proj * view * model;

    // set MVP matrix
    GLint mvp_location = m_program->uniform_location("vs_mvp");
    ogl_assert(mvp_location != -1);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

    // render the thing
    m_vao->activate_vertex_buffer(BINDING_INDEX, m.buffer(), sizeof(vertex));
    glDrawArrays(GL_TRIANGLES, 0, m.count());
    m_vao->unactivate_vertex_buffer(BINDING_INDEX);
  }

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

void renderer::clear_buffer(int width, int height)
{
  // update viewport dimensions
  glViewport(0, 0, width, height);

  // clear buffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
