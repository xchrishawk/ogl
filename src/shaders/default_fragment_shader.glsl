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
  vec3 position;
  vec3 normal;
  vec4 color;
  vec2 texture_coord;
} inblock;

// -- Constants --

const vec3 LIGHT_POSITION = vec3(1.0, 1.0, 2.0);
const vec4 LIGHT_COLOR = vec4(1.0, 0.4, 1.0, 1.0);

// -- Procedures --

void main(void)
{
//  vec3 light_vector = LIGHT_POSITION - inblock.position;
//  float cosTheta = dot(inblock.normal, normalize(light_vector));

  if (texture_available)
    gl_FragColor = texture(texture_sampler, inblock.texture_coord);
  else
    gl_FragColor = inblock.color;
}
