/**
 * @file	vertex_shader.glsl
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#version 330 core

/* -- Uniforms -- */

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

/* -- Inputs -- */

in vec3 vertex_position;
in vec3 vertex_normal;

/* -- Outputs -- */

out VertexBlock
{
  vec3 position;
  vec3 normal;
} outvertex;

/* -- Procedures -- */

void main(void)
{
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);

  outvertex.position = vertex_position;
  outvertex.normal = vertex_normal;
}
