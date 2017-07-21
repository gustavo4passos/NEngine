#version 150 core

in vec3 position;
in vec3 color;
out vec3 fsColor;
uniform mat4 rotate;
uniform mat4 proj;
uniform mat4 view;

void main()
{
  fsColor = color;
  gl_Position =  proj * view * rotate * vec4(position, 1.0);
}
