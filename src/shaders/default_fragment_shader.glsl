#version 330 core

in vec4 fs_color;
in vec3 fs_tex_coord;

uniform sampler2D fs_tex;

void main(void)
{
  gl_FragColor = vec4(fs_tex_coord.x, fs_tex_coord.y, fs_color.z, 1.0f);
}
