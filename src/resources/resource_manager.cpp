/**
 * @file	resource_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

/* -- Includes -- */

#include <map>
#include <memory>
#include <string>

#include "resources/resource_manager.hpp"
#include "resources/shaders/shaders.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

resource_manager::ptr resource_manager::create()
{
  return resource_manager::ptr(new resource_manager(resources::shader_sources));
}

resource_manager::resource_manager(const std::map<std::string, std::string>& shaders)
  : m_shaders(shaders)
{
}

std::string resource_manager::shader_source(const std::string& filename) const
{
  auto it = m_shaders.find(filename);
  if (it == m_shaders.end())
    throw resource_exception("Could not find resource named: " + filename);
  return it->second;
}
