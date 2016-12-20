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

    component();
    component(const component& other);
    component& operator =(const component& other);

    /** Returns the meshes for this component. */
    std::vector<mesh> meshes() const { return m_meshes; }

    /** Sets the meshes for this component. */
    void set_meshes(const std::vector<mesh>& meshes) { m_meshes = meshes; }

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

    /** Returns the innate color of this component. */
    glm::vec4 color() const { return m_color; }

    /** Sets the innate color of this component. */
    void set_color(const glm::vec4& color) { m_color = color; }

  private:

    std::vector<mesh> m_meshes;
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
    glm::vec4 m_color;

  };

}
