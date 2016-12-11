/**
 * mesh.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <memory>
#include <vector>

#include "app/mesh.hpp"
#include "app/vertex.hpp"
#include "opengl/buffer.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const float Z = 0.0f;
  const float U = 0.5f;
  const float D = -0.5f;
  const float F = 0.5f;
  const float B = -0.5f;
  const float R = 0.5f;
  const float L = -0.5f;

  const vertex_color RED = { 1.0f, 0.0f, 0.0f, 1.0f };
  const vertex_color GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
  const vertex_color BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
  const vertex_color CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
  const vertex_color MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
  const vertex_color YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
  const vertex_color WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
  const vertex_color BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
}

/* -- Procedures -- */

mesh::mesh(const vector<vertex>& vertices, const vector<GLuint>& elements)
{
  m_vertex_count = vertices.size();
  m_vertex_buffer = immutable_buffer::create(m_vertex_count * sizeof(vertex), vertices.data(), 0);
  m_element_count = elements.size();
  m_element_buffer = immutable_buffer::create(m_element_count * sizeof(GLuint), elements.data(), 0);
}

mesh example_meshes::rgb_triangle()
{
  vector<vertex> vertices =
  {
    { { Z, Z, Z }, RED },
    { { R, Z, Z }, GREEN },
    { { Z, U, Z }, BLUE },
  };
  vector<GLuint> elements = { 0, 1, 2 };
  return mesh(vertices, elements);
}

mesh example_meshes::cmy_triangle()
{
  vector<vertex> vertices =
  {
    { { Z, Z, Z }, CYAN },
    { { L, Z, Z }, MAGENTA },
    { { Z, D, Z }, YELLOW },
  };
  vector<GLuint> elements = { 0, 1, 2 };
  return mesh(vertices, elements);
}

mesh example_meshes::rgb_cmy_cube()
{
  vector<vertex> vertices =
  {
    { { L, D, B }, RED },		// 0
    { { L, U, B }, GREEN },		// 1
    { { R, D, B }, BLUE },		// 2
    { { R, U, B }, WHITE },		// 3
    { { L, D, F }, WHITE },		// 4
    { { L, U, F }, CYAN },		// 5
    { { R, D, F }, MAGENTA },		// 6
    { { R, U, F }, YELLOW },		// 7
  };
  vector<GLuint> elements =
  {
    0, 1, 2, 2, 3, 1,			// back face
    4, 5, 6, 6, 7, 5,			// front face
    1, 3, 5, 5, 7, 3,			// top face
    0, 2, 4, 4, 6, 2,			// bottom face
    0, 1, 4, 4, 5, 1,			// left face
    2, 3, 6, 6, 7, 3,			// right face
  };
  return mesh(vertices, elements);
}

mesh example_meshes::random_cube()
{
  vector<vertex> vertices =
  {
    // back face
    { { L, D, B }, random_color() },	// 0
    { { R, D, B }, random_color() },	// 1
    { { L, U, B }, random_color() },	// 2
    { { R, U, B }, random_color() },	// 3
  };
  vector<GLuint> elements =
  {
    0, 1, 2, 2, 3, 1,			// back face
  };
}

  vertex_color example_meshes::random_color()
{
  return { ogl_randf(), ogl_randf(), ogl_randf() };
}
