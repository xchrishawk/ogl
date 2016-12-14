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
  vec3 camera_space_position;
  vec3 camera_space_normal;
  vec4 color;
  vec2 texture_coord;
} outvertex;

out PointLightBlock
{
  vec3 camera_space_position;
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
  vec4 model_space_position = vec4(vertex_position, 1.0);
  vec4 world_space_position = model_matrix * model_space_position;
  vec4 camera_space_position = view_matrix * world_space_position;
  vec4 clip_space_position = projection_matrix * camera_space_position;

  // set output position
  gl_Position = clip_space_position;

  // move normal into camera space (fragment shader must normalize)
  vec4 model_space_normal = vec4(vertex_normal, 0.0);
  mat4 normal_matrix = transpose(inverse(model_matrix));
  vec4 world_space_normal = normal_matrix * model_space_normal;
  vec4 camera_space_normal = view_matrix * world_space_normal;

  // set vertex interface block
  outvertex.camera_space_position = camera_space_position.xyz;
  outvertex.camera_space_normal = camera_space_normal.xyz;
  outvertex.color = vertex_color;
  outvertex.texture_coord = vertex_texture_coord;

  // move point light into camera space
  vec4 point_world_space_position = vec4(3.0, 3.0, 7.0, 1.0);
  vec4 point_camera_space_position = view_matrix * point_world_space_position;

  // set point light interface block (constant for now)
  outpointlight.camera_space_position = point_camera_space_position.xyz;
  outpointlight.color = vec4(1.0, 1.0, 1.0, 1.0);
  outpointlight.intensity = 50.0;

  // set ambient light interface block (constant for now)
  outambientlight.color = vec4(0.0, 0.0, 1.0, 1.0);
  outambientlight.intensity = 0.15;
}
