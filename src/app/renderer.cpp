/**
 * @file	renderer.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cmath>
#include <GL/glew.h>

#include "app/renderer.hpp"
#include "app/state.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

void renderer::render(const render_args& args)
{
  glClearColor(fabs(sin(args.abs_t * 200.0f)), fabs(cos(args.abs_t * 200.0f)), 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
