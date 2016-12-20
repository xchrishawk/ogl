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

    static mesh rgb_triangle_mesh();
    static mesh cmy_triangle_mesh();
    static mesh plane(const glm::vec4& color);
    static mesh pyramid(const glm::vec4& color);

  private:

    object_factory() = delete;
    object_factory(const object_factory&) = delete;
    object_factory& operator =(const object_factory&) = delete;

  };

}
