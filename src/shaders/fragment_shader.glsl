#version 330 core

in VertexBlock
{
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture;
} invertex;

void main(void)
{
  gl_FragColor = invertex.color;
}
