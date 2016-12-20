/**
 * @file	renderer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "app/object_factory.hpp"
#include "app/renderer.hpp"
#include "app/state.hpp"
#include "opengl/api.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "scene/component.hpp"
#include "scene/mesh.hpp"
#include "scene/vertex.hpp"
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
    m_vao(renderer::init_vao(m_program))
{
  // one-time initial setup
  enable_depth_testing();
  enable_face_culling();
}

renderer::~renderer()
{
}

void renderer::render(const render_args& args)
{
  clear_buffer(args);
  draw_scene(args);
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

  vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			    program,
			    "vertex_position",
			    vertex::position_count,
			    vertex::position_offset);
  vao->vertex_buffer_format(VERTEX_BUFFER_BINDING,
			    program,
			    "vertex_normal",
			    vertex::normal_count,
			    vertex::normal_offset);

  return vao;
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::draw_scene(const render_args& args)
{
  // init program and VAO
  program::use(m_program);
  vertex_array::bind(m_vao);

  // set uniforms
  set_matrix_uniform("view_matrix", view_matrix(args));
  set_matrix_uniform("projection_matrix", projection_matrix(args));

  // draw each object
  for (const object& obj : args.state.scene().objects())
    draw_object(obj);

  // clean up
  vertex_array::bind_none();
  program::use_none();
}

void renderer::draw_object(const object& obj)
{
  // draw each component in object
  for (const component& comp : obj.components())
  {
    // set uniforms for this component
    set_matrix_uniform("model_matrix", model_matrix(obj, comp));
    set_vec4_uniform("component_color", comp.color());

    // draw each mesh in the component
    for (const mesh& mesh : comp.meshes())
      draw_mesh(mesh);
  }
}

void renderer::draw_mesh(const mesh& mesh)
{
  // bind the vertex and index buffers for this mesh
  m_vao->bind_vertex_buffer(VERTEX_BUFFER_BINDING, mesh.vertex_buffer(), sizeof(vertex), 0);
  m_vao->bind_index_buffer(mesh.index_buffer());

  // draw the mesh
  glDrawElements(mesh.type(), mesh.index_count(), GL_UNSIGNED_INT, nullptr);

  // unbind/clean up
  m_vao->unbind_vertex_buffer(VERTEX_BUFFER_BINDING);
  m_vao->unbind_index_buffer();
}

glm::mat4 renderer::model_matrix(const object& object, const component& component)
{
  // component space -> model space
  glm::mat4 component_matrix =
    glm::translate(component.position()) *
    glm::mat4_cast(component.rotation()) *
    glm::scale(component.scale());

  // model space -> component space
  glm::mat4 object_matrix =
    glm::translate(object.position()) *
    glm::mat4_cast(object.rotation()) *
    glm::scale(object.scale());

  return object_matrix * component_matrix;
}

glm::mat4 renderer::view_matrix(const render_args& args)
{
  glm::mat4 view_matrix =
    glm::translate(args.state.camera_position()) *	// translation (done second)
    glm::mat4_cast(args.state.camera_rotation());	// rotation (done first)
  view_matrix = glm::inverse(view_matrix);		// invert origin->camera into camera->origin

  return view_matrix;
}

glm::mat4 renderer::projection_matrix(const render_args& args)
{
  float aspect_ratio =
    static_cast<float>(args.framebuffer_width) /
    static_cast<float>(args.framebuffer_height);

  glm::mat4 projection_matrix =
    glm::perspective(args.state.camera_fov(),		// camera FOV (Y axis)
		aspect_ratio,				// display aspect ratio
		0.1f,					// near clip (TODO)
		100.0f);				// far clip (TODO)

  return projection_matrix;
}

void renderer::set_vec4_uniform(const std::string& name, const glm::vec4& vector)
{
  GLint location = m_program->uniform_location(name);
  if (location != constants::OPENGL_INVALID_LOCATION)
    glUniform4fv(location, 1, glm::value_ptr(vector));
  else
    ogl_dbg_warning("Did not find uniform location for " + name);
}

void renderer::set_matrix_uniform(const std::string& name, const glm::mat4& matrix)
{
  GLint location = m_program->uniform_location(name);
  if (location != constants::OPENGL_INVALID_LOCATION)
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  else
    ogl_dbg_warning("Did not find uniform location for " + name);
}
