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
  m_program = init_program();
  m_vao = init_vertex_array(m_program);
}

renderer::~renderer()
{
}

void renderer::render(int width, int height, const state& state)
{
  // prepare the framebuffer for drawing
  clear_buffer(width, height);

  // activate program and VAO
  m_program->activate();
  m_vao->activate();

  // get view-projection matrix (same for every object)
  mat4 vp = view_proj_matrix(width, height, state);

  // render each object
  for (object obj : state.objects())
    render_object(vp, obj);

  // deactivate program and VAO
  vertex_array::unactivate();
  program::unactivate();
}

void renderer::render_object(const glm::mat4& vp, ogl::object& obj)
{
  // get and set the model-view-projection matrix
  mat4 mvp = vp * model_matrix(obj);
  glUniformMatrix4fv(m_program->uniform_location("vs_mvp"),
		     1,
		     GL_FALSE,
		     value_ptr(mvp));

  // get mesh we're going to draw
  mesh m = obj.object_mesh();

  // activate vertex and elements buffers for mesh
  m_vao->activate_vertex_buffer(BINDING_INDEX, m.vertex_buffer(), sizeof(vertex));
  m_vao->activate_element_buffer(m.element_buffer());

  // draw the mesh
  glDrawElements(GL_TRIANGLES, m.element_count(), GL_UNSIGNED_INT, nullptr);

  // unactivate vertex and elements buffers for mesh
  m_vao->unactivate_vertex_buffer(BINDING_INDEX);
  m_vao->unactivate_element_buffer();
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

vertex_array::ptr renderer::init_vertex_array(program::ptr program)
{
  vertex_array::ptr vao = vertex_array::create();

  GLint position_attribute = m_program->attribute_location("vs_position");
  ogl_assert(position_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
			    position_attribute,
			    vertex_position::COUNT,
			    offsetof(vertex, position));

  GLint color_attribute = m_program->attribute_location("vs_color");
  ogl_assert(color_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
			    color_attribute,
			    vertex_color::COUNT,
			    offsetof(vertex, color));

  return vao;
}

void renderer::clear_buffer(int width, int height)
{
  // update viewport dimensions
  glViewport(0, 0, width, height);

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // clear buffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

mat4 renderer::view_proj_matrix(int width, int height, const state& state)
{
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

  return proj * view;
}

mat4 renderer::model_matrix(const object& obj)
{
  glm::mat4 model =
    translate(obj.pos()) *				// translation (done third)
    mat4_cast(obj.rot()) *				// rotation (done second)
    scale(obj.scale());					// scale (done first)

  return model;
}
