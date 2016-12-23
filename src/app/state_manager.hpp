/**
 * @file	state_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "scene/scene.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Enumeration of things that keyboard inputs may control.
   */
  enum control_mode
  {
    CONTROL_MODE_CAMERA,		/**< User is controlling the camera. */
    CONTROL_MODE_OBJECT,		/**< User is controlling an object. */
  };

  /**
   * Class containing information required to run a loop of the state manager.
   */
  class state_loop_args
  {
  public:

    state_loop_args(const ogl::input_manager& input_manager,
		    double abs_t,
		    double delta_t)
      : input_manager(input_manager),
	abs_t(abs_t),
	delta_t(delta_t)
    { }

    /** The input manager to use to check input state. */
    const ogl::input_manager& input_manager;

    /** The current absolute run time, in seconds. */
    const double abs_t;

    /** The time since the state loop was last called, in seconds. */
    const double delta_t;

  };

  /**
   * Class managing the application's current state.
   */
  class state_manager : public input_key_observer
  {
  public:

    state_manager();

    /**
     * Runs an iteration of the state loop.
     *
     * @param args
     * The arguments struct containing the information needed for this loop.
     */
    void run(const state_loop_args& args);

    /** Event handler for the `input_key_observer` interface. */
    void input_key_pressed(input_key input);

    /** Returns the scene that should be rendered. */
    ogl::scene scene() const
    { return m_scene; }

  private:

    ogl::control_mode m_control_mode;
    int m_control_object_index;
    ogl::scene m_scene;

    state_manager(const state_manager&) = delete;
    state_manager& operator =(const state_manager&) = delete;

    void default_camera();
    void update_camera(const state_loop_args& args);
    void update_camera_position(const state_loop_args& args);
    void update_camera_rotation(const state_loop_args& args);
    void update_camera_fov(const state_loop_args& args);

    void update_object(const state_loop_args& args);
    void update_object_position(const state_loop_args& args, ogl::object& obj);
    void update_object_rotation(const state_loop_args& args, ogl::object& obj);
    void update_object_scale(const state_loop_args& args, ogl::object& obj);

    glm::vec3 translate(const glm::vec3& position,
			const glm::quat& rotation,
			float rate,
			const state_loop_args& args);
    glm::quat rotate(const glm::quat& quat,
		     float rate,
		     const state_loop_args& args);
    glm::vec3 scale(const glm::vec3& scale,
		    float rate,
		    const state_loop_args& args);

  };

}
