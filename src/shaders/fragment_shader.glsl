/**
 * @file	fragment_shader.glsl
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#version 330 core

/* -- Uniforms -- */

uniform mat4 model_matrix;

uniform vec4 component_color;
uniform vec3 ambient_light;
uniform vec3 directional_light;
uniform vec3 directional_light_direction;

/* -- Inputs -- */

in VertexBlock
{
  vec4 position;
  vec3 normal;
} invertex;

/* -- Outputs -- */

out vec4 fragment_color;

/* -- Procedure Prototypes -- */

vec4 ambient();
vec4 directional();

/* -- Procedures -- */

void main(void)
{
  // In the beginning, there was darkness...
  fragment_color = vec4(0.0);

  // Add light sources
  fragment_color += ambient();
  fragment_color += directional();
}

vec4 ambient()
{
  vec4 intensity = vec4(ambient_light, 1.0);
  return intensity * component_color;
}

vec4 directional()
{
  // rotate normal to world space
  vec4 normal = model_matrix * vec4(invertex.normal, 0.0);

  // we have to invert the direction because math
  vec4 inverted_direction = -1.0 * vec4(directional_light_direction, 1.0);

  // cos theta = Lnorm dot Nnorm
  float cos_theta = dot(normalize(inverted_direction), normalize(normal));

  // get rid of negatives
  cos_theta = clamp(cos_theta, 0.0, 1.0);

  vec4 intensity = cos_theta * vec4(directional_light, 1.0);
  return intensity * component_color;
}
