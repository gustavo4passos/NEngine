#version 150 core

in vec2 position;
in vec2 texcoord;
out vec2 TexCoord;

uniform mat4 ortho;
uniform mat4 transform;
uniform float currentFramex;

void main()
{
  TexCoord = texcoord;
  gl_Position = ortho * transform * vec4(position, 0.0, 1.0);
}
