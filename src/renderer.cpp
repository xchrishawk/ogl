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

  static const GLuint BINDING_INDEX = 0;
  const GLuint POSITION_LOCATION = m_program->attribute_location("vs_position");
  const GLuint COLOR_LOCATION = m_program->attribute_location("vs_color");

  // create VAO
  glCreateVertexArrays(1, &m_vao);

  static const vertex VERTICES[] =
    {
      // CMY triangle
      { -0.5f, -0.5f, -0.2f, 1.0f, 1.0f, 0.0f, 1.0f },
      { 0.5f, 0.0f, -0.2f, 0.0f, 1.0f, 1.0f, 1.0f },
      { 0.0f, 0.5f, -0.2f, 1.0f, 0.0f, 1.0f, 1.0f },

      // RGB triangle
      { 0.5f, 0.5f, -0.1f, 1.0f, 0.0f, 0.0f, 1.0f },
      { -0.5f, 0.0f, -0.1f, 0.0f, 1.0f, 0.0f, 1.0f },
      { 0.0f, -0.5f, -0.1f, 0.0f, 0.0f, 1.0f, 1.0f },
    };

  // create and populate vertex buffer
  glCreateBuffers(1, &m_buffer);
  glNamedBufferStorage(m_buffer,
		       sizeof(VERTICES),
		       VERTICES,
		       0);

  // create buffer binding
  glVertexArrayVertexBuffer(m_vao,
			    BINDING_INDEX,
			    m_buffer,
			    0,
			    sizeof(vertex));

  // initialize vertex positions
  glVertexArrayAttribFormat(m_vao,
			    POSITION_LOCATION,
			    vertex::position_count,
			    GL_FLOAT,
			    GL_FALSE,
			    vertex::position_offset);
  glVertexArrayAttribBinding(m_vao, POSITION_LOCATION, BINDING_INDEX);
  glEnableVertexArrayAttrib(m_vao, POSITION_LOCATION);

  // initialize vertex colors
  glVertexArrayAttribFormat(m_vao,
  			    COLOR_LOCATION,
			    vertex::color_count,
  			    GL_FLOAT,
  			    GL_FALSE,
			    vertex::color_offset);
  glVertexArrayAttribBinding(m_vao, COLOR_LOCATION, BINDING_INDEX);
  glEnableVertexArrayAttrib(m_vao, COLOR_LOCATION);

}

renderer::~renderer()
{
  glDeleteBuffers(1, &m_buffer);
  glDeleteVertexArrays(1, &m_vao);
}

void renderer::loop(const state& state)
{
  clear();
}

void renderer::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GREATER);

  glUseProgram(m_program->id());
  glBindVertexArray(m_vao);

  glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);

  glBindVertexArray(0);
  glUseProgram(0);
}
