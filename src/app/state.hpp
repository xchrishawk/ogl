/**
 * @file	state.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "app/input.hpp"
#include "scene/scene.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to run a loop of the state object.
   */
  class state_args
  {
  public:

    state_args(const ogl::input& input, double abs_t, double delta_t)
      : input(input),
	abs_t(abs_t),
	delta_t(delta_t)
    { }

    const ogl::input& input;
    const double abs_t;
    const double delta_t;

  };

  /**
   * Class representing the current state of the application.
   */
  class state
  {
  public:

    state();

    /** Runs a loop of the state object. */
    void run(const state_args& args);

    /** Returns the position of the camera, in world space. */
    glm::vec3 camera_position() const { return m_camera_position; }

    /** Returns the rotation of the camera, in world space. */
    glm::quat camera_rotation() const { return m_camera_rotation; }

    /** Returns the field of view of the camera, in radians. */
    float camera_fov() const { return m_camera_fov; }

    /** The scene which should be rendered. */
    ogl::scene scene() const { return m_scene; }

  private:

    glm::vec3 m_camera_position;
    glm::quat m_camera_rotation;
    float m_camera_fov;
    ogl::scene m_scene;

    state(const state&) = delete;
    state& operator =(const state&) = delete;

    void update_camera_position(const state_args& args);
    void update_camera_rotation(const state_args& args);
    void update_camera_fov(const state_args& args);

  };

}
