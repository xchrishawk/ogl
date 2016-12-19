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
  : m_objects()
{
}

scene::scene(const std::vector<object>& objects)
  : m_objects(objects)
{
}
