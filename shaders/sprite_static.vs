#version 150 core

in vec2 position;
in vec2 texcoord;
uniform mat4 ortho;
uniform mat4 camera;
out vec2 TexCoord;

void main()
{
  TexCoord = texcoord;
  gl_Position = ortho * camera * vec4(position, 0, 1.0);
}
