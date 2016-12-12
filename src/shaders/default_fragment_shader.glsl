#version 330 core

in vec4 fs_color;
in vec2 fs_tex_coord;

uniform bool fs_tex_avail;
uniform sampler2D fs_tex;

void main(void)
{
  gl_FragColor = fs_tex_avail ? texture(fs_tex, fs_tex_coord) : fs_color;
}
