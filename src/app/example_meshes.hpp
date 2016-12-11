/**
 * example_meshes.hpp
 * Chris Vig (chris@invictus.so)
 */

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

    static ogl::mesh rgb_triangle();
    static ogl::mesh rgb_square();
    static ogl::mesh cmy_triangle();
    static ogl::mesh cmy_square();
    static ogl::mesh rgb_cmy_cube();
    static ogl::mesh random_cube();

  private:

    // not instantiable
    example_meshes() = delete;
    example_meshes(const example_meshes&) = delete;
    example_meshes& operator =(const example_meshes&) = delete;

    static vertex_color random_color();

  };

}
