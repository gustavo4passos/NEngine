#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Texture.h"
#include "Shader.h"
#include "../util/Vector2D.h"
#include <GL/gl.h>

class GameObject
{
public:
  ~GameObject() {}
  virtual void update(unsigned int gameTime) = 0;
  virtual void draw() = 0;

protected:
  unsigned _width;
  unsigned _height;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Texture* _texture;
};

#endif
