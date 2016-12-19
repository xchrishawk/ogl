#version 330 core

in VertexBlock
{
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture;
} invertex;

out vec4 fragment_color;

void main(void)
{
  fragment_color = invertex.color;
}
