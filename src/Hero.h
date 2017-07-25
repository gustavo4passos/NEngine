#ifndef HERO_H
#define HERO_H

#include "GameObject.h"
#include "Texture.h"
#include "Shader.h"
#include "../util/Vector2.h"
#include <GL/gl.h>

class Hero : public GameObject
{
public:
  Hero(const char* textureFilePath, int width, int height, Shader* shader, float frames = 4, float framesh = 1);
  virtual void update(unsigned int gameTime);
  virtual void draw();

private:
  unsigned int _width;
  unsigned int _height;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Texture* texture;
};

#endif
