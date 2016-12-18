#version 330 core

in vec3 vertex_position;
in vec4 vertex_color;

out vec4 fs_vertex_color;

void main(void)
{
  gl_Position = vec4(vertex_position, 1.0);
  fs_vertex_color = vertex_color;
}
