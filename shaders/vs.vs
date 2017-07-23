#version 400 core

in vec3 position;
in vec3 color;
out vec3 fsColor;
uniform mat4 rotate;
uniform mat4 proj;
uniform mat4 view;

in vec2 texcoord;
out vec2 TexCoord;

void main()
{
  fsColor = color;
  TexCoord = texcoord;
  gl_Position =  proj * view * rotate * vec4(position, 1.0);
}
