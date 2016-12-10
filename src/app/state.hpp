/**
 * state.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_STATE_HPP
#define OGL_APP_STATE_HPP

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "app/input.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing the current state of the application.
   */
  class state
  {
  public:

    state();
    ~state();

    void update(float abs_t, float delta_t, const ogl::input& input);

    glm::vec3 camera_pos() const { return m_camera_pos; }
    glm::quat camera_rot() const { return m_camera_rot; }
    float camera_fov() const { return m_camera_fov; }

  private:

    glm::vec3 m_camera_pos;
    glm::quat m_camera_rot;
    float m_camera_fov;

    state(const state&) = delete;
    state& operator =(const state&) = delete;

    void update_camera_pos(float delta_t, const ogl::input& input);
    void update_camera_rot(float delta_t, const ogl::input& input);
    void update_camera_fov(float delta_t, const ogl::input& input);

  };

}

#endif /* OGL_APP_STATE_HPP */
