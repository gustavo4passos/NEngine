#version 400 core

in vec3 fsColor;
out vec4 outColor;
in vec2 TexCoord;
uniform sampler2D sampler;

void main()
{
  vec4 mycolor = texture(sampler, TexCoord);
  outColor = mix(mycolor, (vec4(fsColor, 1.0) * vec4(0.5, 0.5, 0.0, 1.0)), 0.2);
}
