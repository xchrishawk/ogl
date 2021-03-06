/**
 * @file	object_factory.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

#include "scene/component.hpp"
#include "scene/mesh.hpp"
#include "scene/object.hpp"
#include "scene/vertex.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class for building standard objects.
   */
  class object_factory
  {
  public:

    /**
     * Returns a mesh for a 3-dimensional origin crosshair.
     */
    static mesh origin();

    /**
     * Returns a mesh for a square in the X-Y plane, centered at the origin, with
     * dimensions of 1.0 x 1.0 x 0.0.
     */
    static mesh plane();

    /**
     * Returns a mesh for a cube, centered at the origin, with dimensions of
     * 1.0 x 1.0 x 1.0.
     */
    static mesh cube();

    /**
     * Returns a mesh for a smooth cone, centered at the origin, with radius of
     * 1.0 and height of 1.0.
     */
    static mesh cone(int sides);

  private:

    object_factory() = delete;
    object_factory(const object_factory&) = delete;
    object_factory& operator =(const object_factory&) = delete;

  };

}
