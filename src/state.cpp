/**
 * state.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cmath>
#include <iostream>
#include <vector>

#include "key_input.hpp"
#include "mesh.hpp"
#include "state.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedures -- */

state::state()
{
  static const vertex RGB_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f	},
    {	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f	},
    {	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f	},
  };
  m_meshes.push_back(mesh::create(RGB_VERTICES, 3));

  static const vertex CMY_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f	},
    {	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f	},
    {	0.0f,	-0.5f,	0.0f,	.0f,	0.0f,	1.0f,	1.0f	},
  };
  m_meshes.push_back(mesh::create(CMY_VERTICES, 3));
}

void state::loop(float abs_t, float delta_t, const key_input& key_input)
{
}
