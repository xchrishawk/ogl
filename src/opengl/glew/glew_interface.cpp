/**
 * @file	glew_interface.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

/* -- Includes -- */

#include <stdexcept>

#include <GL/glew.h>

#include "opengl/opengl.hpp"
#include "opengl/glew/glew_interface.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl::glew;

/* -- Procedures -- */

ogl::opengl::ptr glew_interface::create()
{
  return ogl::opengl::ptr(new glew_interface());
}

glew_interface::glew_interface()
  : opengl()
{
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW.");

  ogl_dbg_status("GLEW initialized.");
}

glew_interface::~glew_interface()
{
  ogl_dbg_status("GLEW terminated.");
}
