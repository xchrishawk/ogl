/**
 * @file	vertex.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

#include "opengl/api.hpp"
#include "util/debug.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct representing a vertex in a mesh.
   */
  struct vertex
  {
  public:

    static const GLsizei position_count = sizeof(glm::vec3) / sizeof(glm::vec3::value_type);
    static const GLsizei normal_count = sizeof(glm::vec3) / sizeof(glm::vec3::value_type);

    // we cannot use offsetof() inside the struct definition, so we declare these
    // manually here and statically verify them with asserts below
    static const GLsizei position_offset = 0;
    static const GLsizei normal_offset = 12;

    glm::vec3 position;
    glm::vec3 normal;

  };

  ogl_static_assert(vertex::position_offset == offsetof(vertex, position), "Offset incorrect!");
  ogl_static_assert(vertex::normal_offset == offsetof(vertex, normal), "Offset incorrect!");

}
