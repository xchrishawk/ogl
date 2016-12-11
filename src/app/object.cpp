/**
 * object.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "app/mesh.hpp"
#include "app/object.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;
using namespace glm;

/* -- Procedures -- */

object::object(const mesh& object_mesh, const vec3& pos, const quat& rot, const vec3& scale)
  : m_object_mesh(object_mesh),
    m_pos(pos),
    m_rot(rot),
    m_scale(scale)
{
}
