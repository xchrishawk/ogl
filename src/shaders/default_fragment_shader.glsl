//
// default_fragment_shader.glsl
// Chris Vig (chris@invictus.so)
//

#version 330 core

// -- Uniforms --

uniform bool texture_available;
uniform sampler2D texture_sampler;

// -- Inputs --

in VertexFragmentBlock
{
  vec4 color;
  vec2 texture_coord;
} inblock;

// -- Procedures --

void main(void)
{
  if (texture_available)
    gl_FragColor = texture(texture_sampler, inblock.texture_coord);
  else
    gl_FragColor = inblock.color;
}
