#include <string>
#include <stdio.h>
#include "Shader.h"
#include "../util/FileReader.h"

// Shader constructor
// It loads a file from a string, compile, check for errors, and return a Shader object containing a vertex shader and fragment shader linked into a shader program
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
  _id = glCreateProgram();
  glAttachShader(_id, vertexShader);
  glAttachShader(_id, fragmentShader);
  glLinkProgram(_id);

  // Delete shaders because they are already in the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
      printf("GL ERROR: Error during shader creation. %s\n", gluErrorString(error));
    }
}

// Set as the active shader
void Shader::use()
{
  glUseProgram(_id);
}

void Shader::vertexAttribPointer(const char* attribName, unsigned int size, unsigned int stride, unsigned int offset)
{
  GLint attribLocation = glGetAttribLocation(_id, attribName);
  if(attribLocation < 0)
  {
    printf("OPENGL SHADER ERROR: Unable to find attrib location. Attrib: %s\n", attribName);
  }
  else
  {
    glVertexAttribPointer(attribLocation, size, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride,(GLvoid*)(sizeof(GLfloat) * offset));
    glEnableVertexAttribArray(attribLocation);

    // Check for errors
    GLenum error = glGetError();
    while(error != GL_NO_ERROR)
    {
      printf("OPENGL SHADER ERROR: Error while loading vertex attrib data. Attrib: %s. Error: %s\n", attribName, gluErrorString(error));
      error = glGetError();
    }
  }
}

// Loads a flot into the shader
void Shader::setUniform1f(const char* uniformName, GLfloat value)
{
  GLint uniformLocation = glGetUniformLocation(_id, uniformName);
  if(uniformLocation < 0)
  {
    printf("OPENGL SHADER ERROR: Unable to find uniform: %s\n", uniformName);
  }
  else
  {
    glUniform1f(uniformLocation, value);
  }
}

// Load a 4 floats into memory
void Shader::setUniform4f(const char* uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  GLuint uniformLocation = glGetUniformLocation(_id, uniformName);
  // If unable to find uniform
  if(uniformLocation < 0)
  {
    printf("OPENGL SHADER ERROR: Unable to find uniform. %s\n", uniformName);
  }
  else
  {
    glUniform4f(uniformLocation, x, y, z, w);
  }
}

void Shader::setUniform2fv(const char* uniformName, GLfloat* data)
{
  GLint uniformLocation = glGetUniformLocation(_id, uniformName);
  if(uniformLocation < 0)
  {
    printf("OPENGL SHADER ERROR: Unable to find uniform: %s\n", uniformName);
  }
  else
  {
    glUniform2fv(uniformLocation, 1, data);
  }
}

// Loads a 4x4 matris into the shader
void Shader::setMat4(const char* uniformName, const GLfloat* matrix) const
{
  GLint uniformLocation = glGetUniformLocation(_id, uniformName);

  if(uniformLocation < 0)
  {
    printf("OPENGL SHADER ERROR: Unable to find Mat4 uniform: %s\n", uniformName);
  }
  else
  {
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matrix);
  }
}
