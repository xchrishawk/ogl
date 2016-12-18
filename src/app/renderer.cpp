/**
 * @file	renderer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cmath>

#include "app/renderer.hpp"
#include "app/state.hpp"
#include "opengl/api.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"
#include "shaders/shader_manager.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

renderer::renderer()
  : m_program(renderer::init_program())
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
