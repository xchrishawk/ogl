/**
 * shader_source.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

/* -- Includes -- */

#include <string>
#include "opengl.hpp"

/* -- Constants -- */

namespace ogl
{
  extern const GLuint POSITION_ATTRIBUTE_LOCATION;
  extern const GLuint COLOR_ATTRIBUTE_LOCATION;
  extern const GLuint TRANSFORM_UNIFORM_LOCATION;

  extern const std::string VERTEX_SHADER_SOURCE;
  extern const std::string FRAGMENT_SHADER_SOURCE;
}

#endif /* SHADER_SOURCE_HPP */
