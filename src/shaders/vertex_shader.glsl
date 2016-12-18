#version 330 core

uniform float abs_t;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec4 vertex_color;
in vec2 vertex_texture;

out VertexBlock
{
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture;
} outvertex;

void main(void)
{
  gl_Position = vec4(vertex_position, 1.0);

  outvertex.position = vertex_position;
  outvertex.normal = vertex_normal;
  outvertex.color = vertex_color;
  outvertex.texture = vertex_texture;
}
