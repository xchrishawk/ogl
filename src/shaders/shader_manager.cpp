/**
 * @file	shader_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <string>

#include "shaders/shader_manager.hpp"
#include "util/misc.hpp"

/* -- Private Constants -- */

namespace
{

  const char VERTEX_SHADER_SOURCE_ARRAY[] =
  {
    #include "vertex_shader.glsl.inc"
  };

  const char FRAGMENT_SHADER_SOURCE_ARRAY[] =
  {
    #include "fragment_shader.glsl.inc"
  };

}

/* -- Public Constants -- */

#define SHADER(name)								\
  const std::string ogl::shaders::name (name ## _ARRAY, ogl_array_size(name ## _ARRAY))

SHADER(VERTEX_SHADER_SOURCE);
SHADER(FRAGMENT_SHADER_SOURCE);
