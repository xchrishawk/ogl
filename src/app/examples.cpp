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
  const float POS = 1.0f;
  const float NEG = -POS;

  const float Z = 0.0f;
  const float U = POS;
  const float D = NEG;
  const float R = POS;
  const float L = NEG;
  const float F = POS;
  const float B = NEG;

  const vertex_color WHITE	= { 1.0f, 1.0f, 1.0f, 1.0f };
  const vertex_color BLACK	= { 0.0f, 0.0f, 0.0f, 1.0f };
  const vertex_color RED 	= { 1.0f, 0.0f, 0.0f, 1.0f };
  const vertex_color GREEN	= { 0.0f, 1.0f, 0.0f, 1.0f };
  const vertex_color BLUE	= { 0.0f, 0.0f, 1.0f, 1.0f };
  const vertex_color CYAN	= { 0.0f, 1.0f, 1.0f, 1.0f };
  const vertex_color MAGENTA	= { 1.0f, 0.0f, 1.0f, 1.0f };
  const vertex_color YELLOW	= { 1.0f, 1.0f, 0.0f, 1.0f };
}

/* -- Procedures -- */

mesh example_meshes::rgb_triangle()
{
  static const vector<vertex> vertices =
  {
    { { Z, Z, Z }, RED },
    { { R, Z, Z }, GREEN },
    { { Z, U, Z }, BLUE },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLES, { 0, 1, 2 })
  };
  return mesh(vertices, elements);
}

mesh example_meshes::rgb_square()
{
  static const vector<vertex> vertices =
  {
    { { Z, Z, Z }, RED },
    { { L, Z, Z }, GREEN },
    { { L, U, Z }, WHITE },
    { { Z, U, Z }, BLUE },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 })
  };
  return mesh(vertices, elements);
}

mesh example_meshes::cmy_triangle()
{
  static const vector<vertex> vertices =
  {
    { { Z, Z, Z }, CYAN },
    { { L, Z, Z }, MAGENTA },
    { { Z, D, Z }, YELLOW },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLES, { 0, 1, 2 })
  };
  return mesh(vertices, elements);
}

mesh example_meshes::cmy_square()
{
  static const vector<vertex> vertices =
  {
    { { Z, Z, Z }, CYAN },
    { { R, Z, Z }, MAGENTA },
    { { R, D, Z }, WHITE },
    { { Z, D, Z }, YELLOW },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 })
  };
  return mesh(vertices, elements);
}

mesh example_meshes::rgb_cmy_cube()
{
  static const vector<vertex> vertices =
  {
    { { L, D, B }, WHITE },
    { { R, D, B }, RED },
    { { L, U, B }, GREEN },
    { { R, U, B }, BLUE },
    { { L, D, F }, CYAN },
    { { R, D, F }, MAGENTA },
    { { L, U, F }, YELLOW },
    { { R, U, F }, WHITE },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 3, 2 }),	// back
    mesh_elements(GL_TRIANGLE_FAN, { 4, 5, 7, 6 }),	// front
    mesh_elements(GL_TRIANGLE_FAN, { 0, 2, 6, 4 }),	// left
    mesh_elements(GL_TRIANGLE_FAN, { 1, 3, 7, 5 }),	// right
    mesh_elements(GL_TRIANGLE_FAN, { 2, 3, 7, 6 }),	// top
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 5, 4 }),	// bottom
  };
  return mesh(vertices, elements);
}

mesh example_meshes::random_cube()
{
  vector<vertex> vertices =
  {
    // front face
    { { L, D, F }, random_color() },	// 0
    { { R, D, F }, random_color() },	// 1
    { { R, U, F }, random_color() },	// 2
    { { L, U, F }, random_color() },	// 3

    // back face
    { { L, D, B }, random_color() },	// 4
    { { R, D, B }, random_color() },	// 5
    { { R, U, B }, random_color() },	// 6
    { { L, U, B }, random_color() },	// 7

    // left face
    { { L, D, B }, random_color() },	// 8
    { { L, D, F }, random_color() },	// 9
    { { L, U, F }, random_color() },	// 10
    { { L, U, B }, random_color() },	// 11

    // right face
    { { R, D, B }, random_color() },	// 12
    { { R, D, F }, random_color() },	// 13
    { { R, U, F }, random_color() },	// 14
    { { R, U, B }, random_color() },	// 15

    // top face
    { { L, U, B }, random_color() },	// 16
    { { R, U, B }, random_color() },	// 17
    { { R, U, F }, random_color() },	// 18
    { { L, U, F }, random_color() },	// 19

    // bottom face
    { { L, D, B }, random_color() },	// 20
    { { R, D, B }, random_color() },	// 21
    { { R, D, F }, random_color() },	// 22
    { { L, D, F }, random_color() },    // 23
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 }),	// front face
    mesh_elements(GL_TRIANGLE_FAN, { 4, 5, 6, 7 }),	// back face
    mesh_elements(GL_TRIANGLE_FAN, { 8, 9, 10, 11 }),	// left face
    mesh_elements(GL_TRIANGLE_FAN, { 12, 13, 14, 15 }),	// right face
    mesh_elements(GL_TRIANGLE_FAN, { 16, 17, 18, 19 }),	// top face
    mesh_elements(GL_TRIANGLE_FAN, { 20, 21, 22, 23 }), // bottom face
  };
  return mesh(vertices, elements);
}

mesh example_meshes::textured_square()
{
  static const vector<vertex> vertices =
  {
    { { L, D, Z }, BLACK, { 0.0f, 0.0f } },
    { { R, D, Z }, BLACK, { 1.0f, 0.0f } },
    { { R, U, Z }, BLACK, { 1.0f, 1.0f } },
    { { L, U, Z }, BLACK, { 0.0f, 1.0f } },
  };
  vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 }, example_textures::red_white_checker()),
  };
  return mesh(vertices, elements);
}

mesh example_meshes::textured_cube()
{
  vector<vertex> vertices =
  {
    // front face
    { { L, D, F }, MAGENTA, { 0.0f, 0.0f } },
    { { R, D, F }, MAGENTA, { 1.0f, 0.0f } },
    { { R, U, F }, MAGENTA, { 1.0f, 1.0f } },
    { { L, U, F }, MAGENTA, { 0.0f, 1.0f } },

    // back face
    { { L, D, B }, MAGENTA, { 0.0f, 0.0f } },
    { { R, D, B }, MAGENTA, { 1.0f, 0.0f } },
    { { R, U, B }, MAGENTA, { 1.0f, 1.0f } },
    { { L, U, B }, MAGENTA, { 0.0f, 1.0f } },

    // left face
    { { L, D, B }, MAGENTA, { 0.0f, 0.0f } },
    { { L, D, F }, MAGENTA, { 1.0f, 0.0f } },
    { { L, U, F }, MAGENTA, { 1.0f, 1.0f } },
    { { L, U, B }, MAGENTA, { 0.0f, 1.0f } },

    // right face
    { { R, D, B }, MAGENTA, { 0.0f, 0.0f } },
    { { R, D, F }, MAGENTA, { 1.0f, 0.0f } },
    { { R, U, F }, MAGENTA, { 1.0f, 1.0f } },
    { { R, U, B }, MAGENTA, { 0.0f, 1.0f } },

    // top face
    { { L, U, B }, MAGENTA, { 0.0f, 0.0f } },
    { { R, U, B }, MAGENTA, { 1.0f, 0.0f } },
    { { R, U, F }, MAGENTA, { 1.0f, 1.0f } },
    { { L, U, F }, MAGENTA, { 0.0f, 1.0f } },

    // bottom face
    { { L, D, B }, MAGENTA, { 0.0f, 0.0f } },
    { { R, D, B }, MAGENTA, { 1.0f, 0.0f } },
    { { R, D, F }, MAGENTA, { 1.0f, 1.0f } },
    { { L, D, F }, MAGENTA, { 0.0f, 1.0f } },
  };
  static const vector<mesh_elements> elements =
  {
    mesh_elements(GL_TRIANGLE_FAN, { 0, 1, 2, 3 }, example_textures::red_white_checker()),
    mesh_elements(GL_TRIANGLE_FAN, { 4, 5, 6, 7 }, example_textures::red_white_checker()),
    mesh_elements(GL_TRIANGLE_FAN, { 8, 9, 10, 11 }, example_textures::red_white_checker()),
    mesh_elements(GL_TRIANGLE_FAN, { 12, 13, 14, 15 }, example_textures::red_white_checker()),
    mesh_elements(GL_TRIANGLE_FAN, { 16, 17, 18, 19 }, example_textures::red_white_checker()),
    mesh_elements(GL_TRIANGLE_FAN, { 20, 21, 22, 23 }, example_textures::red_white_checker()),
  };
  return mesh(vertices, elements);
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
