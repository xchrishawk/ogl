#version 330 core

uniform vec4 component_color;

in VertexBlock
{
  vec3 position;
  vec3 normal;
} invertex;

out vec4 fragment_color;

void main(void)
{
  fragment_color = component_color;
}
