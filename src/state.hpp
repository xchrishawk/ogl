/**
 * state.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef STATE_HPP
#define STATE_HPP

/* -- Includes -- */

#include <vector>

#include "key_input.hpp"
#include "mesh.hpp"
#include "opengl.hpp"

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

    void loop(float abs_t, float delta_t, const key_input& key_input);

    const glm::quat& camera_rot() const { return m_camera_rot; }
    const glm::vec3& camera_pos() const { return m_camera_pos; }
    float camera_fov() const { return m_camera_fov; }
    const std::vector<mesh::const_ptr>& meshes() const { return m_meshes; }

  private:

    glm::quat m_camera_rot;
    glm::vec3 m_camera_pos;
    float m_camera_fov;
    std::vector<mesh::const_ptr> m_meshes;

    state(const state& other) = delete;
    state& operator =(const state& other) = delete;

    void update_camera_rot(float delta_t, const key_input& key_input);
    void update_camera_pos(float delta_t, const key_input& key_input);
    void update_camera_fov(float delta_t, const key_input& key_input);

  };

}

#endif /* STATE_HPP */
