/**
 * @file	object.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "scene/component.hpp"
#include "scene/object.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

object::object(const std::vector<component>& components,
	       const glm::vec3& position,
	       const glm::quat& rotation,
	       const glm::vec3& scale)
  : m_components(components),
    m_position(position),
    m_rotation(rotation),
    m_scale(scale)
{
}

object::object(const object& other)
  : m_components(other.m_components),
    m_position(other.m_position),
    m_rotation(other.m_rotation),
    m_scale(other.m_scale)
{
}

object& object::operator =(const object& other)
{
  m_components = other.m_components;
  m_position = other.m_position;
  m_rotation = other.m_rotation;
  m_scale = other.m_scale;

  return *this;
}
