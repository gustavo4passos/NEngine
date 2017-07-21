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

  void setFloat(const char* uniformName, GLfloat value);
  void setBool(const char* uniformName, GLboolean value);
  void setVec2(const char* uniformName, GLfloat* array);
  void setVec3(const char* uniformName, GLfloat* array);
  void setVec4(const char* uniformName, GLfloat* array);


private:
  GLuint _shaderID;
  GLenum _shaderType;
};

#endif
