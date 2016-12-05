/**
 * shader_source.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <string>
#include "shader_source.hpp"

/* -- Macros -- */

#define GLSL_HASH(name, value)							\
  "#" name " " value "\n"

/* -- Constants -- */

const GLuint ogl::POSITION_ATTRIBUTE_LOCATION = 0;
const GLuint ogl::COLOR_ATTRIBUTE_LOCATION = 1;
const GLuint ogl::TRANSFORM_UNIFORM_LOCATION = 2;

const std::string ogl::VERTEX_SHADER_SOURCE =
  GLSL_HASH("version", "330 core")
  GLSL_HASH("extension", "GL_ARB_explicit_uniform_location : require")
  R"GLSL(

layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec4 vs_color;
layout (location = 2) uniform mat4 transform;
out vec4 fs_color;

void main(void)
{
  gl_Position = transform * vec4(vs_position.x, vs_position.y, vs_position.z, 1.0);
  fs_color = vs_color;
}

)GLSL";

const std::string ogl::FRAGMENT_SHADER_SOURCE =
  GLSL_HASH("version", "330 core")
  R"GLSL(

in vec4 fs_color;

void main(void)
{
  gl_FragColor = fs_color;
}

)GLSL";
