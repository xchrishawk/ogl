/**
 * @file	object_factory.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include <glm/glm.hpp>

#include "app/object_factory.hpp"
#include "opengl/api.hpp"
#include "scene/component.hpp"
#include "scene/object.hpp"
#include "scene/vertex.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

mesh object_factory::plane()
{
  static const glm::vec3 NORMAL = { 0.0f, 0.0f, 1.0f };

  std::vector<vertex> vertices =
  {
    { { -1.0f, -1.0f, 0.0f }, NORMAL },	// 0
    { { 1.0f, -1.0f, 0.0f }, NORMAL },	// 1
    { { -1.0f, 1.0f, 0.0f }, NORMAL },	// 2
    { { 1.0f, 1.0f, 0.0f }, NORMAL },	// 3
  };
  std::vector<GLuint> indices = { 0, 1, 2, 1, 3, 2 };

  return mesh(GL_TRIANGLES, vertices, indices);
}

mesh object_factory::pyramid()
{
  static const glm::vec3 NE_CORNER = { 1.0f, 1.0f, 0.0f };
  static const glm::vec3 SE_CORNER = { 1.0f, -1.0f, 0.0f };
  static const glm::vec3 NW_CORNER = { -1.0f, 1.0f, 0.0f };
  static const glm::vec3 SW_CORNER = { -1.0f, -1.0f, 0.0f };
  static const glm::vec3 APEX = { 0.0f, 0.0f, 1.0f };

  static const float SQRT2 = 0.707107;

  static const glm::vec3 S_NORMAL = { 0.0f, -SQRT2, SQRT2 };
  static const glm::vec3 N_NORMAL = { 0.0f, SQRT2, SQRT2 };
  static const glm::vec3 W_NORMAL = { -SQRT2, 0.0f, SQRT2 };
  static const glm::vec3 E_NORMAL = { SQRT2, 0.0f, SQRT2 };

  std::vector<vertex> vertices =
  {
    // south face
    { SW_CORNER, S_NORMAL },
    { SE_CORNER, S_NORMAL },
    { APEX, S_NORMAL },

    // north face
    { NE_CORNER, N_NORMAL },
    { NW_CORNER, N_NORMAL },
    { APEX, N_NORMAL },

    // west face
    { NW_CORNER, W_NORMAL },
    { SW_CORNER, W_NORMAL },
    { APEX, W_NORMAL },

    // east face
    { SE_CORNER, E_NORMAL },
    { NE_CORNER, E_NORMAL },
    { APEX, E_NORMAL },
  };
  std::vector<GLuint> indices =
  {
    0, 1, 2, // south face
    3, 4, 5, // north face
    6, 7, 8, // west face
    9, 10, 11, // east face
  };

  return mesh(GL_TRIANGLES, vertices, indices);
}
