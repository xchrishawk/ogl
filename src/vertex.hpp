/**
 * vertex.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

/* -- Includes -- */

#include <cstddef>
#include "util.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct representing a vertex.
   */
  struct vertex
  {
    static const size_t position_offset = 0;
    static const size_t position_count = 3;

    float x;
    float y;
    float z;

    static const size_t color_offset = position_count * sizeof(float);
    static const size_t color_count = 4;

    float r;
    float g;
    float b;
    float a;
  };

  ogl_static_assert(vertex::position_offset == offsetof(vertex, x), "incorrect position offset");
  ogl_static_assert(vertex::color_offset == offsetof(vertex, r), "incorrect color offset");

}

#endif /* VERTEX_HPP */
