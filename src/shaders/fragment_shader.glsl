#version 330 core

// -- Uniforms --

uniform vec3 ambient_light;
uniform vec4 component_color;

// -- Inputs --

in VertexBlock
{
  vec3 position;
  vec3 normal;
} invertex;

// -- Outputs --

out vec4 fragment_color;

// -- Main Procedures --

void main(void)
{
  // Initially start at black
  fragment_color = vec4(0.0);

  // Add ambient lighting
  fragment_color += component_color * vec4(ambient_light, 1.0);
}
