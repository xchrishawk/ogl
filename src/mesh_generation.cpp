/**
 * mesh_generation.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

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
    {	R,	U,	F,	1.0f,	0.0f,	0.0f,	1.0f	},	// 0 - right upper front
    {	R,	U,	B,	0.0f,	1.0f,	0.0f,	1.0f	},	// 1 - right upper back
    {	R,	D,	F,	0.0f,	0.0f,	1.0f,	1.0f	},	// 2 - right lower front
    {	R,	D,	B,	1.0f,	1.0f,	1.0f,	1.0f	},	// 3 - right lower back
    {	L,	U,	F,	1.0f,	1.0f,	1.0f,	1.0f	},	// 4 - left upper front
    {	L,	U,	B,	1.0f,	1.0f,	0.0f,	1.0f	},	// 5 - left upper back
    {	L,	D,	F,	0.0f,	1.0f,	1.0f,	1.0f	},	// 6 - left lower front
    {	L,	D,	B,	1.0f,	0.0f,	1.0f,	1.0f	},	// 7 - left lower back
  };

  static const GLuint RUF = 0;
  static const GLuint RUB = 1;
  static const GLuint RDF = 2;
  static const GLuint RDB = 3;
  static const GLuint LUF = 4;
  static const GLuint LUB = 5;
  static const GLuint LDF = 6;
  static const GLuint LDB = 7;
  GLuint indices[] =
  {
    RUF, RUB, RDF, RDF, RDB, RUB,	// right face
    LUF, LUB, LDF, LDF, LDB, LUB,	// left face
    LUF, RUF, LUB, LUB, RUB, RUF,	// upper face
    LDF, RDF, LDB, LDB, RDB, RDF,	// lower face
    RUF, RDF, LDF, LDF, LUF, RUF,	// front face
    RUB, RDB, LDB, LDB, LUB, RUB,	// back face
  };

  return mesh::create(vertices, ogl_array_size(vertices), indices, ogl_array_size(indices));
}
