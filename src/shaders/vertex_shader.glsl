#version 330 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

in vec3 vertex_position;
in vec3 vertex_normal;

out VertexBlock
{
  vec3 position;
  vec3 normal;
} outvertex;

void main(void)
{
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);

  outvertex.position = vertex_position;
  outvertex.normal = vertex_normal;
}
