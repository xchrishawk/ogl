#version 330 core

in vec3 vs_position;
in vec4 vs_color;
in vec2 vs_tex_coord;

uniform mat4 vs_mvp;

out vec4 fs_color;
out vec2 fs_tex_coord;

void main(void)
{
  gl_Position = vs_mvp * vec4(vs_position.x, vs_position.y, vs_position.z, 1.0);

  fs_color = vs_color;
  fs_tex_coord = vs_tex_coord;
}
