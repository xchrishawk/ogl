/**
 * renderer.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

renderer::renderer()
{
}

renderer::~renderer()
{
}

void renderer::render(float abs_t, float delta_t)
{
  clear_buffer();
}

void renderer::clear_buffer()
{
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
