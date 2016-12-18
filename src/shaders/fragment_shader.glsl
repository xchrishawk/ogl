#version 330 core

uniform float abs_t;

in VertexBlock
{
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture;
} invertex;

void main(void)
{
  gl_FragColor = vec4(abs(sin(abs_t)), abs(cos(abs_t)), 1.0, 1.0);
}
