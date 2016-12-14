//
// default_vertex_shader.glsl
// Chris Vig (chris@invictus.so)
//

#version 330 core

// -- Uniforms --

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

// -- Inputs --

in vec3 vertex_position;
in vec3 vertex_normal;
in vec4 vertex_color;
in vec2 vertex_texture_coord;

// -- Outvertexs --

out VertexBlock
{
  vec3 world_space_position;
  vec3 world_space_normal;
  vec4 color;
  vec2 texture_coord;
} outvertex;

out PointLightBlock
{
  vec3 world_space_position;
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
  // move position through MVP matrix
  vec4 model_space_position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
  vec4 world_space_position = model_matrix * model_space_position;
  vec4 camera_space_position = view_matrix * world_space_position;
  vec4 clip_space_position = projection_matrix * camera_space_position;

  // set output position
  gl_Position = clip_space_position;

  // move normal into world space (fragment shader must normalize)
  vec4 model_space_normal = vec4(vertex_normal.x, vertex_normal.y, vertex_normal.z, 1.0);
  vec4 world_space_normal = model_matrix * model_space_normal;

  // set vertex interface block
  outvertex.world_space_position = world_space_position.xyz;
  outvertex.world_space_normal = world_space_normal.xyz;
  outvertex.color = vertex_color;
  outvertex.texture_coord = vertex_texture_coord;

  // set point light interface block (constant for now)
  outpointlight.world_space_position = vec3(10.0, 10.0, 10.0);
  outpointlight.color = vec4(1.0, 1.0, 1.0, 1.0);
  outpointlight.intensity = 800.0;

  // set ambient light interface block (constant for now)
  outambientlight.color = vec4(0.0, 0.0, 1.0, 1.0);
  outambientlight.intensity = 0.15;
}
