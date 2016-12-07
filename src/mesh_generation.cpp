/**
 * mesh_generation.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "mesh.hpp"
#include "mesh_generation.hpp"
#include "opengl.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Procedure Prototypes -- */

namespace
{
  float rndf();
}

/* -- Procedures -- */

mesh::ptr ogl::cube_mesh()
{
  const float R = 0.5f;
  const float L = -0.5f;
  const float U = 0.5f;
  const float D = -0.5f;
  const float F = 0.5f;
  const float B = -0.5f;
  vertex vertices[] =
  {
    // front face
    { 	R,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},

    // back face
    { 	R,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},

    // top face
    { 	R,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},

    // bottom face
    { 	R,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},

    // left face
    { 	L,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	L,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},

    // right face
    { 	R,	U,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	D,	F,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	U,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
    {	R,	D,	B,	rndf(),	rndf(),	rndf(),	1.0f	},
  };

  GLuint indices[] =
  {
     0,  1,  2,  2,  3,  1,	// front face
     4,  5,  6,  6,  7,  5,	// back face
     8,  9, 10, 10, 11,  9,	// top face
    12, 13, 14, 14, 15, 13,	// bottom face
    16, 17, 18, 18, 19, 17,	// left face
    20, 21, 22, 22, 23, 21,	// right face
  };

  return mesh::create(vertices, ogl_array_size(vertices), indices, ogl_array_size(indices));
}

namespace
{

  float rndf()
  {
    static bool seeded = false;
    if (!seeded)
    {
      srand(time(NULL));
      seeded = true;
    }
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

}
