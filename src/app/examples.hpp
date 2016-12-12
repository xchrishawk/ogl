/**
 * examples.hpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include "app/mesh.hpp"
#include "opengl/texture.hpp"

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

    static ogl::mesh textured_square();
    static ogl::mesh textured_cube();

  private:

    // not instantiable
    example_meshes() = delete;
    example_meshes(const example_meshes&) = delete;
    example_meshes& operator =(const example_meshes&) = delete;

    static vertex_color random_color();

  };

  class example_textures
  {
  public:

    static ogl::texture2d::const_ptr red_white_checker();

  private:

    // not instantiable
    example_textures() = delete;
    example_textures(const example_textures&) = delete;
    example_textures& operator =(const example_textures&) = delete;

  };

}
