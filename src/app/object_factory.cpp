/**
 * @file	object_factory.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include "app/object_factory.hpp"
#include "opengl/api.hpp"
#include "scene/component.hpp"
#include "scene/object.hpp"
#include "scene/vertex.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

mesh object_factory::rgb_triangle_mesh()
{
  static const std::vector<vertex> VERTICES =
  {
    { { 0.0f, 0.0f, 0.0f }, { }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { { 1.0f, 0.0f, 0.0f }, { }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.0f, 1.0f, 0.0f }, { }, { 0.0f, 0.0f, 1.0f, 1.0f } },
  };
  static const std::vector<GLuint> INDICES = { 0, 1, 2 };

  return mesh(GL_TRIANGLES, VERTICES, INDICES);
}

mesh object_factory::cmy_triangle_mesh()
{
  static const std::vector<vertex> VERTICES =
  {
    { { 0.0f, 0.0f, 0.0f }, { }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { 1.0f, 0.0f, 0.0f }, { }, { 1.0f, 0.0f, 1.0f, 1.0f } },
    { { 0.0f, 1.0f, 0.0f }, { }, { 1.0f, 1.0f, 0.0f, 1.0f } },
  };
  static const std::vector<GLuint> INDICES = { 0, 1, 2 };

  return mesh(GL_TRIANGLES, VERTICES, INDICES);
}
