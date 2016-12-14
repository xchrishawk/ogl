//
// default_fragment_shader.glsl
// Chris Vig (chris@invictus.so)
//

#version 330 core

// -- Uniforms --

uniform bool texture_available;
uniform sampler2D texture_sampler;

// -- Inputs --

in VertexBlock
{
  vec3 world_space_position;
  vec3 world_space_normal;
  vec4 color;
  vec2 texture_coord;
} invertex;

in PointLightBlock
{
  vec3 world_space_position;
  vec4 color;
  float intensity;
} inpointlight;

in AmbientLightBlock
{
  vec4 color;
  float intensity;
} inambientlight;

// -- Procedures --

void main(void)
{
  vec3 pointlight_delta = inpointlight.world_space_position - invertex.world_space_position;
  float pointlight_dist = length(pointlight_delta);
  float pointlight_costheta = dot(normalize(invertex.world_space_normal), normalize(pointlight_delta));
  pointlight_costheta = clamp(pointlight_costheta, 0, 1);

  vec4 diffuse =
    inpointlight.intensity *
    inpointlight.color *
    pointlight_costheta *
    (1.0 / (pointlight_dist * pointlight_dist));

  vec4 ambient =
    inambientlight.intensity *
    inambientlight.color;

  gl_FragColor = (invertex.color * diffuse) + (invertex.color * ambient);
}
