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
    static const GLsizei color_count = sizeof(glm::vec4) / sizeof(glm::vec4::value_type);
    static const GLsizei texture_count = sizeof(glm::vec2) / sizeof(glm::vec2::value_type);

    // we cannot use offsetof() inside the struct definition, so we declare these
    // manually here and statically verify them with asserts below
    static const GLsizei position_offset = 0;
    static const GLsizei normal_offset = 12;
    static const GLsizei color_offset = 24;
    static const GLsizei texture_offset = 40;

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 texture;

  };

  ogl_static_assert(vertex::position_offset == offsetof(vertex, position), "Offset incorrect!");
  ogl_static_assert(vertex::normal_offset == offsetof(vertex, normal), "Offset incorrect!");
  ogl_static_assert(vertex::color_offset == offsetof(vertex, color), "Offset incorrect!");
  ogl_static_assert(vertex::texture_offset == offsetof(vertex, texture), "Offset incorrect!");

}
