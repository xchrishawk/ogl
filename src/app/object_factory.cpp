/**
 * @file	object_factory.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "app/object_factory.hpp"
#include "opengl/api.hpp"
#include "scene/component.hpp"
#include "scene/object.hpp"
#include "scene/vertex.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

mesh object_factory::origin()
{
  static const std::vector<vertex> vertices =
  {
    { { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
  };
  static const std::vector<GLuint> indices = { 0, 1, 2, 3, 4, 5 };

  return mesh(GL_LINES, vertices, indices);
}

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

mesh object_factory::cube()
{
  static const float P = 0.5f;
  static const float N = -P;
  static const float Z = 0.0f;

  static const std::vector<vertex> vertices =
  {
    // positive X face
    { { P, N, N }, { P, Z, Z } },
    { { P, P, N }, { P, Z, Z } },
    { { P, P, P }, { P, Z, Z } },
    { { P, N, P }, { P, Z, Z } },

    // negative X face
    { { N, N, N }, { N, Z, Z } },
    { { N, N, P }, { N, Z, Z } },
    { { N, P, P }, { N, Z, Z } },
    { { N, P, N }, { N, Z, Z } },

    // positive Y face
    { { N, P, P }, { Z, P, Z } },
    { { P, P, P }, { Z, P, Z } },
    { { P, P, N }, { Z, P, Z } },
    { { N, P, N }, { Z, P, Z } },

    // negative Y face
    { { N, N, P }, { Z, N, Z } },
    { { N, N, N }, { Z, N, Z } },
    { { P, N, N }, { Z, N, Z } },
    { { P, N, P }, { Z, N, Z } },

    // positive Z face
    { { N, N, P }, { Z, Z, P } },
    { { P, N, P }, { Z, Z, P } },
    { { P, P, P }, { Z, Z, P } },
    { { N, P, P }, { Z, Z, P } },

    // negative Z face
    { { N, N, N }, { Z, Z, N } },
    { { N, P, N }, { Z, Z, N } },
    { { P, P, N }, { Z, Z, N } },
    { { P, N, N }, { Z, Z, N } },
  };
  static const std::vector<GLuint> indices =
  {
    0, 1, 2, 2, 3, 0, 		// positive X face
    4, 5, 6, 6, 7, 4,		// negative X face
    8, 9, 10, 10, 11, 8,	// positive Y face
    12, 13, 14, 14, 15, 12,	// negative Y face
    16, 17, 18, 18, 19, 16,	// positive Z face
    20, 21, 22, 22, 23, 20,	// negative Z face
  };

  return mesh(GL_TRIANGLES, vertices, indices);
}

mesh object_factory::cone(int sides)
{
  ogl_dbg_assert(sides > 2);

  // arc angle that each side subtends
  const float theta_per_side = (2.0f * M_PI) / sides;

  // vectors to hold vertices and indices
  std::vector<vertex> vertices;
  vertices.reserve(sides * 3);
  std::vector<GLuint> indices;
  indices.reserve(sides * 3);

  // current vertex index that we're working on
  int vertex_index = 0;

  for (int side = 0; side < sides; side++)
  {
    // angles of vertices
    float theta_v1 = side * theta_per_side;
    float theta_v2 = (side + 1) * theta_per_side;

    // first vertex
    glm::vec3 v1 = rotateZ(constants::VEC3_UNIT_X, theta_v1);
    glm::vec3 n1 = rotateZ(constants::VEC3_UNIT_X, theta_v1);
    vertices.push_back({ v1, n1 });
    indices.push_back(vertex_index++);

    // second vertex
    glm::vec3 v2 = rotateZ(constants::VEC3_UNIT_X, theta_v2);
    glm::vec3 n2 = rotateZ(constants::VEC3_UNIT_X, theta_v2);
    vertices.push_back({ v2, n2 });
    indices.push_back(vertex_index++);

    // third vertex
    glm::vec3 v3 = constants::VEC3_UNIT_Z;
    glm::vec3 n3 = constants::VEC3_UNIT_Z;
    vertices.push_back({ v3, n3 });
    indices.push_back(vertex_index++);
  }

  return mesh(GL_TRIANGLES, vertices, indices);
}
