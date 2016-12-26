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
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{

  /* -- Shader Arrays -- */

  const char SIMPLE_VERTEX_SHADER_SOURCE_ARRAY[] = {
    #include "shaders/simple_vertex_shader.glsl.inc"
  };
  const char SIMPLE_FRAGMENT_SHADER_SOURCE_ARRAY[] = {
    #include "shaders/simple_fragment_shader.glsl.inc"
  };

  /* -- Shader Lookup -- */

  const std::map<std::string, std::string> SHADER_SOURCE_LOOKUP = {
    { "shaders/simple_vertex_shader.glsl", char_array_to_string(SIMPLE_VERTEX_SHADER_SOURCE_ARRAY) },
    { "shaders/simple_fragment_shader.glsl", char_array_to_string(SIMPLE_FRAGMENT_SHADER_SOURCE_ARRAY) },
  };

}

/* -- Procedures -- */

resource_manager::ptr resource_manager::create()
{
  return resource_manager::ptr(new resource_manager());
}

std::string resource_manager::shader_source(const std::string& filename) const
{
  auto it = SHADER_SOURCE_LOOKUP.find(filename);
  if (it == SHADER_SOURCE_LOOKUP.end())
    throw resource_exception("Could not find shader source named: " + filename);
  return it->second;
}
