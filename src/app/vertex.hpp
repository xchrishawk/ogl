/**
 * vertex.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_VERTEX_HPP
#define OGL_APP_VERTEX_HPP

/* -- Includes -- */

#include <cstddef>
#include <GL/glew.h>

#include "util/debug.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct representing the position of a vertex.
   */
  struct vertex_position
  {

    static const GLsizei COUNT = 3;

    float x;	/* x position */
    float y;	/* y position */
    float z;	/* z position */

  };
  ogl_static_assert(sizeof(vertex_position) == vertex_position::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing the color of a vertex.
   */
  struct vertex_color
  {

    static const GLsizei COUNT = 4;

    float r;	/* red component */
    float g;	/* green component */
    float b;	/* blue component */
    float a;	/* alpha component */

  };
  ogl_static_assert(sizeof(vertex_color) == vertex_color::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing the texture coordinates of a vertex.
   */
  struct vertex_texture
  {

    static const GLsizei COUNT = 2;

    float r;	/* texture x coordinate */
    float s;	/* texture y coordinate */

  };
  ogl_static_assert(sizeof(vertex_texture) == vertex_texture::COUNT * sizeof(float), "Wrong struct size!");

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
