/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "app/renderer.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "opengl/vertex_array.hpp"
#include "shaders/shader_sources.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const vertex VERTICES_1[] = {
    { {	0.0f,	0.0f,	0.0f 	}, {	1.0f, 	0.0f, 	0.0f,	1.0f,	}, {	0.0f,	0.0f	} },
    { {	0.5f,	0.0f,	0.0f	}, {	0.0f,	1.0f,	0.0f,	1.0f,	}, {	0.0f,	0.0f	} },
    { {	0.0f,	0.5f,	0.0f	}, {	0.0f,	0.0f,	1.0f,	1.0f,	}, {	0.0f,	0.0f	} },
  };
  const size_t VERTEX_COUNT_1 = ogl_array_size(VERTICES_1);

  const vertex VERTICES_2[] = {
    { {	0.0f,	0.0f,	0.0f 	}, {	0.0f, 	1.0f, 	1.0f,	1.0f,	}, {	0.0f,	0.0f	} },
    { {	-0.5f,	0.0f,	0.0f	}, {	1.0f,	0.0f,	1.0f,	1.0f,	}, {	0.0f,	0.0f	} },
    { {	0.0f,	-0.5f,	0.0f	}, {	1.0f,	1.0f,	0.0f,	1.0f,	}, {	0.0f,	0.0f	} },
  };
  const size_t VERTEX_COUNT_2 = ogl_array_size(VERTICES_2);

  const GLuint BINDING_INDEX = 0;
}

/* -- Procedures -- */

renderer::renderer()
  : m_vao()
{
  m_vao = vertex_array::create();
  m_buffer_1 = immutable_buffer::create(sizeof(VERTICES_1), VERTICES_1, 0);
  m_buffer_2 = immutable_buffer::create(sizeof(VERTICES_2), VERTICES_2, 0);
  m_program = init_program();

  init_attribute_binding("vs_position", BINDING_INDEX, vertex_position::COUNT, offsetof(vertex, position));
  init_attribute_binding("vs_color", BINDING_INDEX, vertex_color::COUNT, offsetof(vertex, color));
}

renderer::~renderer()
{
}

void renderer::render(float abs_t, float delta_t)
{
  clear_buffer();

  m_program->activate();
  m_vao->bind();

  glBindVertexBuffer(0, m_buffer_1->handle(), 0, sizeof(vertex));
  glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT_1);
  glBindVertexBuffer(0, 0, 0, 0);

  glBindVertexBuffer(0, m_buffer_2->handle(), 0, sizeof(vertex));
  glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT_2);
  glBindVertexBuffer(0, 0, 0, 0);

  vertex_array::unbind();
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

void renderer::init_attribute_binding(const std::string& attribute_name,
				      GLuint binding_index,
				      GLint size,
				      GLint relative_offset)
{
  // get attribute location from program
  GLint attribute_location = m_program->attribute_location(attribute_name);
  ogl_assert(attribute_location != -1);

  // set format of the attribute
  glVertexArrayAttribFormat(m_vao->handle(),			// vaobj
			    attribute_location,			// attribindex
			    size,				// size
			    GL_FLOAT,				// type
			    GL_FALSE,				// normalized
			    relative_offset);			// relativeoffset

  // associate the attribute with buffer binding
  glVertexArrayAttribBinding(m_vao->handle(),			// vaobj
			     attribute_location,		// attribindex
			     binding_index);			// bindingindex

  // enable array access for the attribute
  glEnableVertexArrayAttrib(m_vao->handle(),			// vaobj
			    attribute_location);		// attribindex
}

void renderer::clear_buffer()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
