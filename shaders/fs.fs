#version 400 core

in vec3 fsColor;
out vec4 outColor;
in vec2 TexCoord;
uniform sampler2D sampler;
in vec3 Normal;
in vec3 fragPos;
uniform vec3 lightPos;
vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main()
{
<<<<<<< HEAD
  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  vec4 mycolor = texture(sampler, TexCoord);
  vec3 result = (ambient + diffuse);
  outColor = mix(mycolor, (vec4(fsColor, 1.0) * vec4(0.5, 0.5, 0.0, 1.0)), 0.2) * vec4(result, 1.0);

  if(gl_FragCoord.x == lightPos.x)
  {
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
  }
=======
  vec4 mycolor = texture(sampler, TexCoord);
  outColor = mix(mycolor, (vec4(fsColor, 1.0) * vec4(0.5, 0.5, 0.0, 1.0)), 0.2);
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b
}
