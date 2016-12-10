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

  // enable position attribute
  GLuint position_attribute_location = m_program->attribute_location("vs_position");
  glVertexArrayAttribFormat(m_vao->handle(),			// vaobj
			    position_attribute_location,	// attribindex
			    3,					// size
			    GL_FLOAT,				// type
			    GL_FALSE,				// normalized
			    offsetof(vertex, position));	// relativeoffset
  glVertexArrayAttribBinding(m_vao->handle(),			// vaobj
			     position_attribute_location,	// attribindex
			     BINDING_INDEX);			// bindingindex
  glEnableVertexArrayAttrib(m_vao->handle(),			// vaobj
			    position_attribute_location);	// index

  // enable color attribute
  GLuint color_attribute_location = m_program->attribute_location("vs_color");
  glVertexArrayAttribFormat(m_vao->handle(),			// vaobj
			    color_attribute_location,		// attribindex
			    3,					// size
			    GL_FLOAT,				// type
			    GL_FALSE,				// normalized
			    offsetof(vertex, color));		// relativeoffset
  glVertexArrayAttribBinding(m_vao->handle(),			// vaobj
			     color_attribute_location,		// attribindex
			     BINDING_INDEX);			// bindingindex
  glEnableVertexArrayAttrib(m_vao->handle(),			// vaobj
			    color_attribute_location);		// index
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

void renderer::clear_buffer()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
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
