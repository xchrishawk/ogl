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

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

void renderer::render(const render_args& args)
{
  glClearColor(fabs(sin(args.abs_t)), fabs(cos(args.abs_t)), 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
