/**
 * @file	scene.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include "scene/object.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Top level class representing a scene to be rendered by the application.
   */
  class scene
  {
  public:

    /** Creates a new, empty scene. */
    scene();

    /** Creates a new scene with the specified object list. */
    scene(const std::vector<object>& objects);

    /** Returns the objects included in this scene. */
    std::vector<object> objects() const { return m_objects; }

  private:

    std::vector<object> m_objects;

  };

}
