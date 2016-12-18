/**
 * @file	renderer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

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
    m_vao(renderer::init_vao(m_program)),
    m_object(renderer::init_object())
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
  draw_object(m_object);
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
    ogl_dbg_warning("Did not find attribute location for vertex_position");
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
    ogl_dbg_warning("Did not find attribute location for vertex_normal");
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
    ogl_dbg_warning("Did not find attribute location for vertex_color");
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
    ogl_dbg_warning("Did not find attribute location for vertex_texture");
  }

  return vao;
}

object renderer::init_object()
{
  static const std::vector<vertex> mesh1_vertices = {
    { { 0.0f, 0.0f, 0.0f }, { }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { { 0.0f, 0.5f, 0.0f }, { }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.5f, 0.0f, 0.0f }, { }, { 0.0f, 0.0f, 1.0f, 1.0f } },
  };
  static const std::vector<GLuint> mesh1_indices = { 0, 1, 2 };
  mesh mesh1(GL_TRIANGLES, mesh1_vertices, mesh1_indices);

  static const std::vector<vertex> mesh2_vertices = {
    { { 0.0f, 0.0f, 0.0f }, { }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { 0.0f, -0.5f, 0.0f }, { }, { 1.0f, 0.0f, 1.0f, 1.0f } },
    { { -0.5f, 0.0f, 0.0f }, { }, { 1.0f, 1.0f, 0.0f, 1.0f } },
  };
  static const std::vector<GLuint> mesh2_indices = { 0, 1, 2 };
  mesh mesh2(GL_TRIANGLES, mesh2_vertices, mesh2_indices);

  ogl::component component1({ mesh1, mesh2 },
			    glm::vec3(-0.5f, 0.5f, 0.0f),
			    glm::quat(),
			    glm::vec3(2.0f, 0.5f, 0.5f));
  ogl::component component2({ mesh1, mesh2 },
			    glm::vec3(0.5f, -0.5f, 0.0f),
			    glm::quat(),
			    glm::vec3(3.0f, 0.5f, 0.5f));

  ogl::object object({ component1, component2 },
		     glm::vec3(0.0f, 0.0f, 0.0f),
		     glm::quat(),
		     glm::vec3(0.333f, 1.0f, 1.0f));

  return object;
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

void renderer::draw_object(const object& object)
{
  // get model->world matrix
  glm::mat4 model_matrix = object.matrix();

  // draw each component in object
  for (const component& comp : object.components())
    draw_component(comp, model_matrix);
}

void renderer::draw_component(const component& component, const glm::mat4& model_matrix)
{
  // create final model matrix, and set uniform with transform
  glm::mat4 matrix = model_matrix * component.matrix();
  glUniformMatrix4fv(m_program->uniform_location("model_matrix"),	// location
		     1,							// count
		     GL_FALSE,						// transpose
		     value_ptr(matrix));				// value

  // draw each mesh in component
  for (const mesh& mesh : component.meshes())
    draw_mesh(mesh);
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
