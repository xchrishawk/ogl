/**
 * vertex.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_VERTEX_HPP
#define OGL_APP_VERTEX_HPP

/* -- Includes -- */

#include <cstddef>
#include "util/debug.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct representing the position of a vertex.
   */
  struct vertex_position
  {
    float x;	/* x position */
    float y;	/* y position */
    float z;	/* z position */
  };

  /**
   * Struct representing the color of a vertex.
   */
  struct vertex_color
  {
    float r;	/* red component */
    float g;	/* green component */
    float b;	/* blue component */
    float a;	/* alpha component */
  };

  /**
   * Struct representing the texture coordinates of a vertex.
   */
  struct vertex_texture
  {
    float r;	/* texture x coordinate */
    float s;	/* texture y coordinate */
    float t;	/* texture z coordinate */
  };

  /**
   * Struct representing a vertex in a mesh.
   */
  struct vertex
  {
    vertex_position position;
    vertex_color color;
    vertex_texture texture;
  };

}

#endif /* OGL_APP_VERTEX_HPP */
