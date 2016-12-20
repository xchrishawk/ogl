/**
 * @file	scene.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/18
 */

/* -- Includes -- */

#include "scene/scene.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

scene::scene()
  : m_objects(),
    m_ambient_light(),
    m_directional_lights()
{
}

scene::scene(const scene& other)
  : m_objects(other.m_objects),
    m_ambient_light(other.m_ambient_light),
    m_directional_lights(other.m_directional_lights)
{
}

scene& scene::operator =(const scene& other)
{
  m_objects = other.m_objects;
  m_ambient_light = other.m_ambient_light;
  m_directional_lights = other.m_directional_lights;

  return *this;
}
