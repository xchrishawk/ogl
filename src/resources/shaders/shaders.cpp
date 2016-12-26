/**
 * @file	shaders.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

/* -- Includes -- */

#include <map>
#include <string>

#include "resources/shaders/shaders.hpp"

/* -- Inline Procedures -- */

namespace
{
  /** Builds a `std::string` from a non-null terminated `char` array. */
  template <size_t size>
  constexpr std::string array_to_string(const char (&array)[size])
  {
    return std::string(array, size);
  }
}

/* -- Constants -- */

namespace
{
  const char SIMPLE_VERTEX_SHADER_SOURCE_ARRAY[] =
  {
    #include "shaders/simple_vertex_shader.glsl.inc"
  };
  const char SIMPLE_FRAGMENT_SHADER_SOURCE_ARRAY[] =
  {
    #include "shaders/simple_fragment_shader.glsl.inc"
  };
}

const std::map<std::string, std::string> ogl::resources::shader_sources =
{
  { "shaders/simple_vertex_shader.glsl", array_to_string(SIMPLE_VERTEX_SHADER_SOURCE_ARRAY) },
  { "shaders/simple_fragment_shader.glsl", array_to_string(SIMPLE_FRAGMENT_SHADER_SOURCE_ARRAY) },
};
