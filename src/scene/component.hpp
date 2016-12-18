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
   */
  class component
  {
  public:

    component(const std::vector<mesh>& meshes,
	      const glm::vec3& position,
	      const glm::quat& rotation,
	      const glm::vec3& scale);

    /** Returns the meshes for this component. */
    std::vector<mesh> meshes() const { return m_meshes; }

    /** Returns the position of this component in object space. */
    glm::vec3 position() const { return m_position; }

    /** Returns the rotation of this component in object space. */
    glm::quat rotation() const { return m_rotation; }

    /** Returns the scaling of this component in object space. */
    glm::vec3 scale() const { return m_scale; }

    /**
     * Returns a transformation matrix to transform this component's mesh vertex
     * coordinates from component space into model space.
     */
    glm::mat4 matrix() const;

  private:

    const std::vector<mesh> m_meshes;
    const glm::vec3 m_position;
    const glm::quat m_rotation;
    const glm::vec3 m_scale;

  };

}
