#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/Glu.h>

class Shader
{
public:
  Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
  GLuint shaderID() const { return _shaderID; }

  void use();

  void setFloat(const char* uniformName, GLfloat value) const;
  void setBool(const char* uniformName, GLboolean value) const;
  void setVec2(const char* uniformName, GLfloat* array) const;
  void setVec3(const char* uniformName, GLfloat* array) const;
  void setVec4(const char* uniformName, GLfloat* array) const;
  void setMat4(const char* uniformName, GLfloat* matrix) const;


private:
  GLuint _shaderID;
  GLenum _shaderType;
};

#endif
