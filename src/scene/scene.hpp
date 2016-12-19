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

    scene(const scene& other);
    scene& operator =(const scene& other);

    /** Returns the objects included in this scene. */
    std::vector<object> objects() const { return m_objects; }

    /** Sets the objects included in this scene. */
    void set_objects(const std::vector<object>& objects) { m_objects = objects; }

  private:

    std::vector<object> m_objects;

  };

}
