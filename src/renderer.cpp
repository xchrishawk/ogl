/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "opengl.hpp"
#include "renderer.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

renderer::renderer()
{

}

void renderer::loop(const state& state)
{
  clear();
}

void renderer::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
