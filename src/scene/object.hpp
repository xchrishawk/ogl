/**
 * @file	object.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "scene/component.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a renderable object in a scene.
   */
  class object
  {
  public:

    object(const std::vector<component>& components,
	   const glm::vec3& position,
	   const glm::quat& rotation,
	   const glm::vec3& scale);

    /** Returns the components which make up this object. */
    std::vector<component> components() const { return m_components; }

    /** Returns the position of this object in world space. */
    glm::vec3 position() const { return m_position; }

    /** Returns the rotation of this object in world space. */
    glm::quat rotation() const { return m_rotation; }

    /** Returns the scaling of this object in world space. */
    glm::vec3 scale() const { return m_scale; }

    /**
     * Returns a transformation matrix to transform this object's mesh vertex
     * coordinates from model space into world space.
     */
    glm::mat4 matrix() const;

  private:

    const std::vector<component> m_components;
    const glm::vec3 m_position;
    const glm::quat m_rotation;
    const glm::vec3 m_scale;

  };

}
