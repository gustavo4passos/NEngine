#version 150 core

in vec2 TexCoord;

uniform sampler2D sampler;

uniform vec2 currentFrame;

out vec4 outColor;

void main()
{
  float framex = TexCoord.x + currentFrame.x;
  float framey = TexCoord.y + currentFrame.y;
  outColor = texture(sampler, vec2(framex, framey));
}
