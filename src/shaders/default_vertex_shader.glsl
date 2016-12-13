//
// default_vertex_shader.glsl
// Chris Vig (chris@invictus.so)
//

#version 330 core

// -- Uniforms --

uniform mat4 mvp;

// -- Inputs --

in vec3 position;
in vec4 color;
in vec2 texture_coord;

// -- Outblocks --

out VertexFragmentBlock
{
  vec4 color;
  vec2 texture_coord;
} outblock;

// -- Procedures --

void main(void)
{
  gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);

  outblock.color = color;
  outblock.texture_coord = texture_coord;
}
