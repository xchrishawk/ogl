/**
 * object.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_OBJECT_HPP
#define OGL_APP_OBJECT_HPP

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "app/mesh.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a renderable object.
   */
  class object
  {
  public:

    object(const ogl::mesh& mesh,
	   const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
	   const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	   const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
      : m_mesh(mesh),
	m_pos(pos),
	m_rot(rot),
	m_scale(scale)
    { }

    ogl::mesh mesh() const { return m_mesh; }
    glm::vec3 pos() const { return m_pos; }
    glm::quat rot() const { return m_rot; }
    glm::vec3 scale() const { return m_scale; }

  private:

    ogl::mesh m_mesh;
    glm::vec3 m_pos;
    glm::quat m_rot;
    glm::vec3 m_scale;

  };

}

#endif /* OGL_APP_OBJECT_HPP */
