/**
 * @file	resource_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

/* -- Includes -- */

#include <map>
#include <memory>
#include <string>

#include "app/resource_manager.hpp"
#include "resources/resources.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

resource_manager::ptr resource_manager::create()
{
  return resource_manager::ptr(new resource_manager());
}

std::string resource_manager::shader_source(const std::string& filename) const
{
  auto it = resources::shader_source_lookup.find(filename);
  if (it == resources::shader_source_lookup.end())
    throw resource_exception("Could not find shader source named: " + filename);
  return it->second;
}
