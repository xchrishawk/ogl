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

/* -- Constants -- */

namespace
{
  // Colors
  const glm::vec4 BLACK_COLOR 		= { 0.0f, 0.0f, 0.0f, 1.0f };
  const glm::vec4 GREY_COLOR		= { 0.5f, 0.5f, 0.5f, 1.0f };
  const glm::vec4 WHITE_COLOR		= { 1.0f, 1.0f, 1.0f, 1.0f };
  const glm::vec4 RED_COLOR		= { 1.0f, 0.0f, 0.0f, 1.0f };
  const glm::vec4 GREEN_COLOR		= { 0.0f, 1.0f, 0.0f, 1.0f };
  const glm::vec4 BLUE_COLOR		= { 0.0f, 0.0f, 1.0f, 1.0f };
  const glm::vec4 CYAN_COLOR		= { 0.0f, 1.0f, 1.0f, 1.0f };
  const glm::vec4 MAGENTA_COLOR		= { 1.0f, 0.0f, 1.0f, 1.0f };
  const glm::vec4 YELLOW_COLOR		= { 1.0f, 1.0f, 0.0f, 1.0f };
}

/* -- Procedures -- */

mesh object_factory::rgb_triangle_mesh()
{
  static const std::vector<vertex> VERTICES =
  {
    { { 0.0f, 0.0f, 0.0f }, { }, RED_COLOR },
    { { 1.0f, 0.0f, 0.0f }, { }, GREEN_COLOR },
    { { 0.0f, 1.0f, 0.0f }, { }, BLUE_COLOR },
  };
  static const std::vector<GLuint> INDICES = { 0, 1, 2 };

  return mesh(GL_TRIANGLES, VERTICES, INDICES);
}

mesh object_factory::cmy_triangle_mesh()
{
  static const std::vector<vertex> VERTICES =
  {
    { { 0.0f, 0.0f, 0.0f }, { }, CYAN_COLOR },
    { { 1.0f, 0.0f, 0.0f }, { }, MAGENTA_COLOR },
    { { 0.0f, 1.0f, 0.0f }, { }, YELLOW_COLOR },
  };
  static const std::vector<GLuint> INDICES = { 0, 1, 2 };

  return mesh(GL_TRIANGLES, VERTICES, INDICES);
}

mesh object_factory::plane(const glm::vec4& color)
{
  static const glm::vec3 NORMAL = { 0.0f, 0.0f, 1.0f };

  std::vector<vertex> vertices =
  {
    { { -1.0f, -1.0f, 0.0f }, NORMAL, color },	// 0
    { { 1.0f, -1.0f, 0.0f }, NORMAL, color },	// 1
    { { -1.0f, 1.0f, 0.0f }, NORMAL, color },	// 2
    { { 1.0f, 1.0f, 0.0f }, NORMAL, color },	// 3
  };
  std::vector<GLuint> indices = { 0, 1, 2, 1, 3, 2 };

  return mesh(GL_TRIANGLES, vertices, indices);
}

mesh object_factory::pyramid(const glm::vec4& color)
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
    { SW_CORNER, S_NORMAL, color },
    { SE_CORNER, S_NORMAL, color },
    { APEX, S_NORMAL, color },

    // north face
    { NE_CORNER, N_NORMAL, color },
    { NW_CORNER, N_NORMAL, color },
    { APEX, N_NORMAL, color },

    // west face
    { NW_CORNER, W_NORMAL, color },
    { SW_CORNER, W_NORMAL, color },
    { APEX, W_NORMAL, color },

    // east face
    { SE_CORNER, E_NORMAL, color },
    { NE_CORNER, E_NORMAL, color },
    { APEX, E_NORMAL, color },
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
