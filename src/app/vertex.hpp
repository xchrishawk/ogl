/**
 * vertex.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_VERTEX_HPP
#define OGL_APP_VERTEX_HPP

/* -- Includes -- */

#include <cstddef>

#include "opengl/opengl.hpp"
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

    float px;	/* x position */
    float py;	/* y position */
    float pz;	/* z position */

  };
  ogl_static_assert(sizeof(vertex_position) == vertex_position::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing the normal of a vertex.
   */
  struct vertex_normal
  {

    static const GLsizei COUNT = 3;

    float nx;	/* x component of normal */
    float ny;	/* y component of normal */
    float nz;	/* z component of normal */

  };
  ogl_static_assert(sizeof(vertex_normal) == vertex_normal::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing the color of a vertex.
   */
  struct vertex_color
  {

    static const GLsizei COUNT = 4;

    float cr;	/* red component */
    float cg;	/* green component */
    float cb;	/* blue component */
    float ca;	/* alpha component */

  };
  ogl_static_assert(sizeof(vertex_color) == vertex_color::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing the texture coordinates of a vertex.
   */
  struct vertex_texture
  {

    static const GLsizei COUNT = 2;

    float tx;	/* texture x coordinate */
    float ty;	/* texture y coordinate */

  };
  ogl_static_assert(sizeof(vertex_texture) == vertex_texture::COUNT * sizeof(float), "Wrong struct size!");

  /**
   * Struct representing a vertex in a mesh.
   */
  struct vertex
  {
    vertex_position position;
    vertex_normal normal;
    vertex_color color;
    vertex_texture texture;
  };

}

#endif /* OGL_APP_VERTEX_HPP */
