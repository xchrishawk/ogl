#version 330 core

in vec3 vs_position;
in vec4 vs_color;
out vec4 fs_color;

void main(void)
{
  gl_Position = vec4(vs_position.x, vs_position.y, vs_position.z, 1.0);
  fs_color = vs_color;
}
