/**
 * @file	scene.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

#include "scene/directional_light.hpp"
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

    /** Creates a new `scene` with default configuration. */
    scene()
      : m_objects(),
	m_ambient_light(1.0),
	m_directional_lights()
    { }

    /** Returns the objects included in this scene. */
    std::vector<object> objects() const
    { return m_objects; }

    /** Sets the objects included in this scene. */
    void set_objects(const std::vector<object>& objects)
    { m_objects = objects; }

    /**
     * Gets the ambient light vector.
     *
     * This is an RGB vector which represents the combined color and intensity
     * of the scene's ambient lighting.
     */
    glm::vec3 ambient_light() const
    { return m_ambient_light; }

    /** Sets the ambient light vector. */
    void set_ambient_light(const glm::vec3& light)
    { m_ambient_light = light; }

    /** Returns the directional lights in the scene. */
    std::vector<directional_light> directional_lights() const
    { return m_directional_lights; }

    /** Sets the directional lights in the scene. */
    void set_directional_lights(const std::vector<directional_light>& lights)
    { m_directional_lights = lights; }

  private:

    std::vector<object> m_objects;
    glm::vec3 m_ambient_light;
    std::vector<directional_light> m_directional_lights;

  };

}
