#ifndef HERO_H
#define HERO_H

#include "GameObject.h"
#include "Texture.h"
#include "Shader.h"
#include "../util/Vector2D.h"
#include <GL/gl.h>

class Hero : public GameObject
{
public:
  Hero(const char* textureFilePath, int x, int y, int width, int height, float speed, Shader* shader, float framesw = 1, float framesh = 1);
  virtual void update(unsigned int gameTime);
  virtual void draw();

private:
  unsigned int _width;
  unsigned int _height;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Texture* _texture;

  Vector2D _position;
  Vector2D _velocity;
  float _speed;
};

#endif
