#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/Glu.h>

class Shader
{
public:
  Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
  GLuint id() const { return _id; }

  // Make itself the current shader program
  void use();

  // Set up attrib array
  void vertexAttribPointer(const char* attribName, unsigned int size, unsigned int stride, unsigned int offset);

  // Loads different types of data into video memory
  void setMat4(const char* uniformName, const GLfloat* matrix) const;
  void setUniform1f(const char* uniformName, GLfloat data);
  void setUniform4f(const char* uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void setUniform2fv(const char* uniformName, GLfloat* data);


private:
  GLuint _id;
  GLenum _shaderType;
};

#endif
