#version 150 core

in vec2 position;
in vec2 texcoord;
uniform mat4 ortho;
out vec2 TexCoord;

void main()
{
  TexCoord = texcoord;
  gl_Position = ortho * vec4(position, 0, 1.0);
}
