#version 150 core

in vec3 fsColor;
out vec4 outColor;
in vec2 Texcoord;
uniform sampler2D sampler;

void main()
{
  vec4 color234 = texture(sampler, Texcoord);
  outColor = vec4(fsColor, 1.0)* vec4(0.5, 0.5, 0.0, 1.0);
}
