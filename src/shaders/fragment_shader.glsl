#version 330 core

in vec4 fs_vertex_color;

void main(void)
{
  gl_FragColor = fs_vertex_color;
}
