#version 150 core

in vec3 position;
in vec3 color;
in vec3 normal;
out vec3 Normal;
out vec3 fsColor;
uniform mat4 rotate;
uniform mat4 proj;
uniform mat4 view;

out vec3 fragPos;
in vec2 texcoord;
out vec2 TexCoord;

void main()
{
  Normal = normal;
  fsColor = color;
  TexCoord = texcoord;
  fragPos = vec3(rotate * vec4(position, 1.0));
  gl_Position =  proj * view * rotate * vec4(position, 1.0);
}
