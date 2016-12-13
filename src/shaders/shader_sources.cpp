/**
 * shader_sources.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <string>

#include "shaders/shader_sources.hpp"
#include "util/misc.hpp"

/* -- Private Constants -- */

namespace
{

  const char DEFAULT_VERTEX_SHADER_SOURCE_ARRAY[] =
  {
    #include "gen/default_vertex_shader.glsl.inc"
  };

  const char DEFAULT_FRAGMENT_SHADER_SOURCE_ARRAY[] =
  {
    #include "gen/default_fragment_shader.glsl.inc"
  };

}

/* -- Public Constants -- */

#define SHADER(name)								\
  const std::string ogl::name (name ## _ARRAY, ogl_array_size(name ## _ARRAY))

SHADER(DEFAULT_VERTEX_SHADER_SOURCE);
SHADER(DEFAULT_FRAGMENT_SHADER_SOURCE);
