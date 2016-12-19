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

    /**
     * Creates a new object instance.
     *
     * @param components
     * The components to include in this object.
     *
     * @param position
     * The initial position of the object, in world space.
     *
     * @param rotation
     * The initial rotation of the object, in world space.
     *
     * @param scale
     * The initial scale of the object, in world space.
     */
    object(const std::vector<component>& components,
	   const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
	   const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	   const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

    object(const object& other);
    object& operator =(const object& other);

    /** Returns the components which make up this object. */
    std::vector<component> components() const { return m_components; }

    /** Returns the position of this object in world space. */
    glm::vec3 position() const { return m_position; }

    /** Sets the position of this object in world space. */
    void set_position(const glm::vec3& position) { m_position = position; }

    /** Returns the rotation of this object in world space. */
    glm::quat rotation() const { return m_rotation; }

    /** Sets the rotation of this object in world space. */
    void set_rotation(const glm::quat& rotation) { m_rotation = rotation; }

    /** Returns the scaling of this object in world space. */
    glm::vec3 scale() const { return m_scale; }

    /** Sets the scale of this object in world space. */
    void set_scale(const glm::vec3& scale) { m_scale = scale; }

    /**
     * Returns a transformation matrix to transform this object's mesh vertex
     * coordinates from model space into world space.
     */
    glm::mat4 matrix() const;

  private:

    std::vector<component> m_components;
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

  };

}
