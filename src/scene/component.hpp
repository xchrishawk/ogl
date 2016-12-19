/**
 * @file	component.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "scene/mesh.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a component in an renderable object.
   *
   * A component represents a "part" of an object which shares a common position,
   * orientation, and scale with respect to the rest of the object. It also
   * has other characteristics such as lighting and/or color.
   */
  class component
  {
  public:

    /**
     * Creates a new component.
     *
     * @parameter meshes
     * The meshes to include in the component.
     *
     * @parameter position
     * The initial position of the component, in model space.
     *
     * @parameter rotation
     * The initial rotation of the component, in model space.
     *
     * @parameter scale
     * The initial scale of the component, in model space.
     */
    component(const std::vector<mesh>& meshes,
	      const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
	      const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	      const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

    component(const component& other);
    component& operator =(const component& other);

    /** Returns the meshes for this component. */
    std::vector<mesh> meshes() const { return m_meshes; }

    /** Returns the position of this component in object space. */
    glm::vec3 position() const { return m_position; }

    /** Sets the position of this component in object space. */
    void set_position(const glm::vec3& position) { m_position = position; }

    /** Returns the rotation of this component in object space. */
    glm::quat rotation() const { return m_rotation; }

    /** Sets the rotation of this component in object space. */
    void set_rotation(const glm::quat& rotation) { m_rotation = rotation; }

    /** Returns the scaling of this component in object space. */
    glm::vec3 scale() const { return m_scale; }

    /** Sets the scale of this component in object space. */
    void set_scale(const glm::vec3& scale) { m_scale = scale; }

  private:

    std::vector<mesh> m_meshes;
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

  };

}
