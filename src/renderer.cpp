/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl.hpp"
#include "program.hpp"
#include "renderer.hpp"
#include "shader.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const size_t VERTEX_COUNT = 3;
  const size_t FLOATS_PER_VERTEX = 4;
  const GLuint BINDING_INDEX = 0;
  const GLuint VERTEX_ATTRIBUTE_INDEX = 0;
}

/* -- Procedures -- */

renderer::renderer()
{
  static const GLuint BINDING_INDEX = 0;

  // create VAO
  glCreateVertexArrays(1, &m_vao);

  static const float VERTICES[] =
    {
      0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.0f, 0.0f, 1.0f,
      0.0f, 0.5f, 0.0f, 1.0f,
    };

  // create and populate vertex buffer
  glCreateBuffers(1, &m_buffer);
  glNamedBufferStorage(m_buffer,
		       sizeof(VERTICES),
		       VERTICES,
		       0);

  // bind buffer
  glVertexArrayVertexBuffer(m_vao,
			    BINDING_INDEX,
			    m_buffer,
			    0,
			    FLOATS_PER_VERTEX * sizeof(float));
  glVertexArrayAttribFormat(m_vao,
			    VERTEX_ATTRIBUTE_INDEX,
			    4,
			    GL_FLOAT,
			    GL_FALSE,
			    0);
  glVertexArrayAttribBinding(m_vao,
			     VERTEX_ATTRIBUTE_INDEX,
			     BINDING_INDEX);
  glEnableVertexArrayAttrib(m_vao,
			    VERTEX_ATTRIBUTE_INDEX);

  auto vertex_shader = shader::create(GL_VERTEX_SHADER);
  vertex_shader->load_source("/home/chris/Developer/ogl/shaders/vertex_shader.glsl");
  vertex_shader->compile();

  auto fragment_shader = shader::create(GL_FRAGMENT_SHADER);
  fragment_shader->load_source("/home/chris/Developer/ogl/shaders/fragment_shader.glsl");
  fragment_shader->compile();

  m_program = program::create();
  m_program->attach_shaders({ vertex_shader, fragment_shader });
  m_program->link();
  m_program->detach_shaders({ vertex_shader, fragment_shader });
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
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(m_program->id());
  glBindVertexArray(m_vao);

  glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);

  glBindVertexArray(0);
  glUseProgram(0);
}
