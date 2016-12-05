/**
 * state.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "key_input.hpp"
#include "mesh.hpp"
#include "state.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

state::state()
  : m_camera_pos(0.0f, 0.0f, 0.0f),
    m_camera_rot(0.0f, 0.0f, 0.0f)
{
  static const vertex RGB_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	-0.2f,	-0.2f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f	},
    {	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f	},
    {	0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f	},
    {	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint RGB_INDICES[] = { 0, 1, 2, 0, 2, 3 };
  m_meshes.push_back(mesh::create(RGB_VERTICES, ogl_array_size(RGB_VERTICES),
				  RGB_INDICES, ogl_array_size(RGB_INDICES)));

  static const vertex CMY_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	0.2f,	0.2f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f	},
    {	-0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f	},
    {	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f	},
    {	0.0f,	-0.5f,	0.0f,	1.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint CMY_INDICES[] = { 0, 1, 2, 0, 2, 3 };
  m_meshes.push_back(mesh::create(CMY_VERTICES, ogl_array_size(CMY_VERTICES),
				  CMY_INDICES, ogl_array_size(CMY_INDICES)));
}

void state::loop(float abs_t, float delta_t, const key_input& key_input)
{
}
