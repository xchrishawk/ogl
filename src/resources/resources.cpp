/**
 * @file	resources.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

/* -- Includes -- */

#include "resources/resources.hpp"
#include "util/misc.hpp"

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

}

const std::map<std::string, std::string> ogl::resources::shader_source_lookup =
{
  { "shaders/simple_vertex_shader.glsl", char_array_to_string(SIMPLE_VERTEX_SHADER_SOURCE_ARRAY) },
  { "shaders/simple_fragment_shader.glsl", char_array_to_string(SIMPLE_FRAGMENT_SHADER_SOURCE_ARRAY) },
};
