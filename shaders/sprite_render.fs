#version 150 core

in vec2 TexCoord;
uniform sampler2D sampler;
out vec4 outColor;

void main()
{
  outColor = texture(sampler, TexCoord);
}
