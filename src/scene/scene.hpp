/**
 * @file	scene.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
      : m_camera_position(),
	m_camera_rotation(),
	m_camera_fov(),
	m_objects(),
	m_ambient_light(1.0),
	m_directional_light(),
	m_directional_light_direction()
    { }

    /** Returns the position of the camera, in world coordinates. */
    glm::vec3 camera_position() const
    { return m_camera_position; }

    /** Sets the position of the camera, in world coordinates. */
    void set_camera_position(const glm::vec3& position)
    { m_camera_position = position; }

    /** Returns the rotation of the camera, in world coordinates. */
    glm::quat camera_rotation() const
    { return m_camera_rotation; }

    /** Sets the rotation of the camera, in world coordinates. */
    void set_camera_rotation(const glm::quat& rotation)
    { m_camera_rotation = rotation; }

    /** Returns the field of view of the camera, in radians. */
    float camera_fov() const
    { return m_camera_fov; }

    /** Sets the field of view of the camera, in radians. */
    void set_camera_fov(float fov)
    { m_camera_fov = fov; }

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

    /**
     * Gets the directional light vector.
     *
     * This is an RGB vector which represents the combined color and intensity
     * of the scene's directional lighting.
     */
    glm::vec3 directional_light() const
    { return m_directional_light; }

    /** Sets the directional light vector. */
    void set_directional_light(const glm::vec3& light)
    { m_directional_light = light; }

    /** Gets the directional light direction. */
    glm::vec3 directional_light_direction() const
    { return m_directional_light_direction; }

    /** Sets the directional light direction. */
    void set_directional_light_direction(const glm::vec3& direction)
    { m_directional_light_direction = direction; }

    /** Returns the number of objects in the scene as an `int`. */
    int object_count() const
    { return static_cast<int>(m_objects.size()); }

  private:

    glm::vec3 m_camera_position;
    glm::quat m_camera_rotation;
    float m_camera_fov;

    std::vector<object> m_objects;

    glm::vec3 m_ambient_light;
    glm::vec3 m_directional_light;
    glm::vec3 m_directional_light_direction;

  };

}
