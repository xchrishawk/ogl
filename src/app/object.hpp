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
   * Class representing a rendered object.
   */
  class object
  {
  public:

    object(const ogl::mesh& object_mesh,
	   const glm::vec3& pos,
	   const glm::quat& rot,
	   const glm::vec3& scale);

    ogl::mesh object_mesh() const { return m_object_mesh; }
    glm::vec3 pos() const { return m_pos; }
    glm::quat rot() const { return m_rot; }
    glm::vec3 scale() const { return m_scale; }

  private:

    ogl::mesh m_object_mesh;
    glm::vec3 m_pos;
    glm::quat m_rot;
    glm::vec3 m_scale;

  };

}

#endif /* OGL_APP_OBJECT_HPP */
