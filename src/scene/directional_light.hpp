/**
 * @file	directional_light.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/19
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a directional light.
   */
  class directional_light
  {
  public:

    /** Returns the direction vector for the light. */
    glm::vec3 direction() const { return m_direction; }

    /** Sets the direction vector for the light. */
    void set_direction(const glm::vec3& direction) { m_direction = direction; }

    /**
     * Returns the light vector.
     *
     * This is an RGB vector which represents the combined color and intensity
     * of the directional light.
     */
    glm::vec3 light() const { return m_light; }

    /** Sets the light vector. */
    void set_light(const glm::vec3& light) { m_light = light; }

  private:

    glm::vec3 m_direction;
    glm::vec3 m_light;

  };

}
