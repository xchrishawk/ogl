/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "app/mesh.hpp"
#include "app/object.hpp"
#include "app/renderer.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "opengl/opengl.hpp"
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

void renderer::render(const renderer_args& args)
{
  // prepare the framebuffer for drawing
  clear_buffer(args.width, args.height);

  // activate program and VAO
  m_program->activate();
  m_vao->activate();

  // get matrices
  mat4 view_matrix = this->view_matrix(args);
  mat4 projection_matrix = this->projection_matrix(args);

  // loop through each object to render
  for (const object& obj : args.state.objects())
    render_object(obj, view_matrix, projection_matrix);

  // deactivate program and VAO
  vertex_array::unactivate();
  program::unactivate();
}


void renderer::clear_buffer(int width, int height)
{
  // update viewport dimensions
  glViewport(0, 0, width, height);

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // enable face culling
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);

  // clear buffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::render_object(const object& obj,
			     const mat4& view_matrix,
			     const mat4& projection_matrix)
{
  // create MVP matrix
  mat4 model_matrix = this->model_matrix(obj);
  mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;

  // set uniforms
  set_matrix_uniform("model_matrix", model_matrix);
  set_matrix_uniform("view_matrix", view_matrix);
  set_matrix_uniform("projection_matrix", projection_matrix);
  set_matrix_uniform("mvp_matrix", mvp_matrix);

  // activate buffer for this object
  mesh obj_mesh = obj.mesh();
  m_vao->activate_vertex_buffer(BINDING_INDEX, obj_mesh.buffer(), sizeof(vertex), 0);

  // render each mesh elements set
  for (const mesh_elements& elements : obj_mesh.elements())
    render_mesh_elements(elements);

  // clean up
  m_vao->unactivate_vertex_buffer(BINDING_INDEX);
}

void renderer::render_mesh_elements(const mesh_elements& elements)
{
  glActiveTexture(GL_TEXTURE0);

  if (elements.texture())
  {
    glBindTexture(GL_TEXTURE_2D, elements.texture()->handle());
    glUniform1i(m_program->uniform_location("texture_sampler"), 0);
    glUniform1i(m_program->uniform_location("texture_available"), true);
  }
  else
  {
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_program->uniform_location("texture_available"), false);
  }

  glDrawElements(elements.mode(), elements.count(), elements.type(), elements.indices());
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

  GLint position_attribute = program->attribute_location("vertex_position");
//  ogl_assert(position_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
  			    position_attribute,
  			    vertex_position::COUNT,
   			    offsetof(vertex, position));

  GLint normal_attribute = program->attribute_location("vertex_normal");
//  ogl_assert(normal_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
			    normal_attribute,
			    vertex_normal::COUNT,
			    offsetof(vertex, normal));

  GLint color_attribute = program->attribute_location("vertex_color");
//  ogl_assert(color_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
   			    color_attribute,
   			    vertex_color::COUNT,
   			    offsetof(vertex, color));

  GLint texture_attribute = program->attribute_location("vertex_texture_coord");
//  ogl_assert(texture_attribute != -1);
  vao->vertex_buffer_format(BINDING_INDEX,
			    texture_attribute,
			    vertex_texture::COUNT,
			    offsetof(vertex, texture));

  return vao;
}

mat4 renderer::model_matrix(const object& obj)
{
  mat4 model_matrix =
    translate(obj.pos()) *			// translation (done third)
    mat4_cast(obj.rot()) *			// rotation (done second)
    scale(obj.scale());				// scaling (done first)

  return model_matrix;
}

mat4 renderer::view_matrix(const renderer_args& args)
{
  mat4 view_matrix =
    translate(args.state.camera_pos()) *	// translation (done second)
    mat4_cast(args.state.camera_rot());		// rotation (done first)
  view_matrix = inverse(view_matrix);		// invert origin->camera into camera->origin

  return view_matrix;
}

mat4 renderer::projection_matrix(const renderer_args& args)
{
  float aspect_ratio =
    static_cast<float>(args.width) /
    static_cast<float>(args.height);

  mat4 projection_matrix =
    perspective(args.state.camera_fov(),	// camera FOV (Y axis)
		aspect_ratio,			// display aspect ratio
		0.1f,				// near clip (TODO)
		100.0f);			// far clip (TODO)

  return projection_matrix;
}

void renderer::set_matrix_uniform(const string& name, const mat4& matrix)
{
  glUniformMatrix4fv(m_program->uniform_location(name),		// location
		     1,						// count
		     GL_FALSE,					// transpose
		     value_ptr(matrix));			// value
}
