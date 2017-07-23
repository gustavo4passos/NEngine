#version 150 core

in vec3 position;
in vec3 color;
out vec3 fsColor;
uniform mat4 rotate;
uniform mat4 proj;
uniform mat4 view;

in vec2 texcoord;
out vec2 Texcoord;

void main()
{
  fsColor = color;
  Texcoord = texcoord;
  gl_Position =  proj * view * rotate * vec4(position, 1.0);
}
