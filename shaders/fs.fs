#version 150 core

in vec3 fsColor;
out vec4 outColor;

void main()
{
  outColor = vec4(fsColor, 1.0)* vec4(0.5, 0.5, 0.0, 1.0);
}
