#include <string>
#include <stdio.h>
#include "Shader.h"
#include "util/FileReader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
  // Read the shader files to strings
  std::string vertexShaderContent = FileReader::readFile(vertexShaderPath);
  std::string fragmentShaderContent = FileReader::readFile(fragmentShaderPath);

  // Convert the strings to C null terminated char arrays
  const GLchar* vertexShaderSource = vertexShaderContent.c_str();
  const GLchar* fragmentShaderSource = fragmentShaderContent.c_str();

  // Create the shader objects
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Compile the vertex shader
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // Check the compile status
  GLint vsCompileStatus;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsCompileStatus);
  // If the shader wasn't compiled successfully, print log
  if(vsCompileStatus != GL_TRUE)
  {
    GLchar buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    printf("GL ERROR: Unable to compile vertex shader. (%s)\n%s", vertexShaderPath, buffer);
  }

  // Compile the fragment shader
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // Check the compile status
  GLint fsCompileStatus;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsCompileStatus);
  // If the shader wasn't compiled successfully, print log
  if(fsCompileStatus != GL_TRUE)
  {
    GLchar buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    printf("GL ERROR: Unable to compile fragment shader. (%s)\n&s", buffer);
  }

  // Create the shader program object, attach shaders and link program
  _shaderID = glCreateProgram();
  glAttachShader(_shaderID, vertexShader);
  glAttachShader(_shaderID, fragmentShader);
  glLinkProgram(_shaderID);

  // Delete shaders because they are already in the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
