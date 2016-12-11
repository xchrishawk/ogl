/**
 * example_meshes.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_PROTOTYPE_EXAMPLE_MESHES_HPP
#define OGL_APP_PROTOTYPE_EXAMPLE_MESHES_HPP

/* -- Includes -- */

#include "app/mesh.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class generating example meshes for prototyping.
   */
  class example_meshes
  {
  public:

    static mesh rgb_triangle();
    static mesh cmy_triangle();
    static mesh rgb_cmy_cube();
    static mesh random_cube();

  private:

    // non-instantiable class
    example_meshes() = delete;
    example_meshes(const example_meshes&) = delete;
    example_meshes& operator =(const example_meshes&) = delete;

    static vertex_color random_color();

  };

}

#endif /* OGL_APP_PROTOTYPE_EXAMPLE_MESHES_HPP */
