/**
 * @file	component.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "scene/component.hpp"
#include "scene/mesh.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

component::component(const std::vector<mesh>& meshes,
		     const glm::vec3& position,
		     const glm::quat& rotation,
		     const glm::vec3& scale)
  : m_meshes(meshes),
    m_position(position),
    m_rotation(rotation),
    m_scale(scale)
{
}

component::component(const component& other)
  : m_meshes(other.m_meshes),
    m_position(other.m_position),
    m_rotation(other.m_rotation),
    m_scale(other.m_scale)
{
}

component& component::operator =(const component& other)
{
  m_meshes = other.m_meshes;
  m_position = other.m_position;
  m_rotation = other.m_rotation;
  m_scale = other.m_scale;

  return *this;
}
