//
// default_vertex_shader.glsl
// Chris Vig (chris@invictus.so)
//

#version 330 core

// -- Uniforms --

uniform mat4 mvp;

// -- Inputs --

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texture_coord;

// -- Outvertexs --

out VertexBlock
{
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture_coord;
} outvertex;

out PointLightBlock
{
  vec3 position;
  vec4 color;
  float intensity;
} outpointlight;

out AmbientLightBlock
{
  vec4 color;
  float intensity;
} outambientlight;

// -- Procedures --

void main(void)
{
  outvertex.position = position;
  outvertex.normal = normal;
  outvertex.color = color;
  outvertex.texture_coord = texture_coord;

  outpointlight.position = vec3(3.0, 3.0, 3.0);
  outpointlight.color = vec4(1.0, 0.0, 0.0, 1.0);
  outpointlight.intensity = 50.0;

  outambientlight.color = vec4(0.0, 1.0, 0.0, 1.0);
  outambientlight.intensity = 0.15;

  gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
}
