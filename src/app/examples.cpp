/**
 * examples.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <vector>

#include <GL/glew.h>

#include "app/examples.hpp"
#include "app/mesh.hpp"
#include "app/vertex.hpp"
#include "opengl/texture.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  // constants
  const float P = 1.0f;
  const float N = -1.0f;
  const float Z = 0.0f;

  // vertex positions
  const float R = P;
  const float L = N;
  const float U = P;
  const float D = N;
  const float F = P;
  const float B = N;

  // vertex normals
  const vertex_normal NORM_POS_X = { P, Z, Z };
  const vertex_normal NORM_NEG_X = { N, Z, Z };
  const vertex_normal NORM_POS_Y = { Z, P, Z };
  const vertex_normal NORM_NEG_Y = { Z, N, Z };
  const vertex_normal NORM_POS_Z = { Z, Z, P };
  const vertex_normal NORM_NEG_Z = { Z, Z, N };

  // vertex colors
  const vertex_color WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
  const vertex_color GRAY = { 0.5f, 0.5f, 0.5f, 1.0f };
  const vertex_color BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
}

/* -- Procedures -- */

mesh example_meshes::gray_cube()
{
  static const vector<vertex> VERTICES =
  {
    // front face
    { { L, D, F }, NORM_POS_Z, GRAY },
    { { R, D, F }, NORM_POS_Z, GRAY },
    { { R, U, F }, NORM_POS_Z, GRAY },
    { { L, U, F }, NORM_POS_Z, GRAY },

    // back face
    { { R, D, B }, NORM_NEG_Z, GRAY },
    { { L, D, B }, NORM_NEG_Z, GRAY },
    { { L, U, B }, NORM_NEG_Z, GRAY },
    { { R, U, B }, NORM_NEG_Z, GRAY },

    // left face
    { { L, D, B }, NORM_NEG_X, GRAY },
    { { L, D, F }, NORM_NEG_X, GRAY },
    { { L, U, F }, NORM_NEG_X, GRAY },
    { { L, U, B }, NORM_NEG_X, GRAY },

    // right face
    { { R, D, F }, NORM_POS_X, GRAY },
    { { R, D, B }, NORM_POS_X, GRAY },
    { { R, U, B }, NORM_POS_X, GRAY },
    { { R, U, F }, NORM_POS_X, GRAY },

    // top face
    { { L, U, B }, NORM_POS_Y, GRAY },
    { { L, U, F }, NORM_POS_Y, GRAY },
    { { R, U, F }, NORM_POS_Y, GRAY },
    { { R, U, B }, NORM_POS_Y, GRAY },

    // bottom face
    { { L, D, B }, NORM_NEG_Y, GRAY },
    { { R, D, B }, NORM_NEG_Y, GRAY },
    { { R, D, U }, NORM_NEG_Y, GRAY },
    { { L, D, U }, NORM_NEG_Y, GRAY },
  };
  static const vector<mesh_elements> ELEMENTS =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 }),
    mesh_elements(GL_TRIANGLE_FAN, { 4, 5, 6, 7 }),
    mesh_elements(GL_TRIANGLE_FAN, { 8, 9, 10, 11 }),
    mesh_elements(GL_TRIANGLE_FAN, { 12, 13, 14, 15 }),
    mesh_elements(GL_TRIANGLE_FAN, { 16, 17, 18, 19 }),
    mesh_elements(GL_TRIANGLE_FAN, { 20, 21, 22, 23 }),
  };
  static const mesh MESH = mesh(VERTICES, ELEMENTS);

  return MESH;
}

vertex_color example_meshes::random_color()
{
  return { ogl_randf(), ogl_randf(), ogl_randf(), 1.0f };
}

texture2d::const_ptr example_textures::red_white_checker()
{
  static const GLsizei WIDTH = 2;
  static const GLsizei HEIGHT = 2;
  static const float PIXELS[] =
  {
    1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
  };
  ogl_static_assert(ogl_array_size(PIXELS) == WIDTH * HEIGHT * 3, "Array wrong size!");

  static texture2d::ptr tex;
  if (!tex)
  {
    tex = texture2d::create(1, GL_RGB32F, WIDTH, HEIGHT);
    tex->set_image(0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_FLOAT, PIXELS);
    tex->set_min_filter(GL_NEAREST);
    tex->set_mag_filter(GL_NEAREST);
  }

  return tex;
}
