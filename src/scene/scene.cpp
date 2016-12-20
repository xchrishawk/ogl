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
    m_ambient_light()
{
}

scene::scene(const scene& other)
  : m_objects(other.m_objects),
    m_ambient_light(other.m_ambient_light)
{
}

scene& scene::operator =(const scene& other)
{
  m_objects = other.m_objects;
  m_ambient_light = other.m_ambient_light;

  return *this;
}
