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

    /** Creates a new `object` with default configuration. */
    object()
      : m_components(),
	m_position(),
	m_rotation(),
	m_scale(1.0)
    { }

    /** Returns the components which make up this object. */
    std::vector<component> components() const
    { return m_components; }

    /** Sets the components which make up this object. */
    void set_components(const std::vector<component>& components)
    { m_components = components; }

    /** Returns the position of this object in world space. */
    glm::vec3 position() const
    { return m_position; }

    /** Sets the position of this object in world space. */
    void set_position(const glm::vec3& position)
    { m_position = position; }

    /** Returns the rotation of this object in world space. */
    glm::quat rotation() const
    { return m_rotation; }

    /** Sets the rotation of this object in world space. */
    void set_rotation(const glm::quat& rotation)
    { m_rotation = rotation; }

    /** Returns the scaling of this object in world space. */
    glm::vec3 scale() const
    { return m_scale; }

    /** Sets the scale of this object in world space. */
    void set_scale(const glm::vec3& scale)
    { m_scale = scale; }

  private:

    std::vector<component> m_components;
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

  };

}
