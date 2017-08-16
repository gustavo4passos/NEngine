#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

class Button : public GameObject
{
public:
  Button(const char* sprite, int x, int y, int width = 0, int height = 0, int frames = 3);
  ~Button();

  virtual void handleInput();
  virtual void update(unsigned int gameTime);
  virtual void draw();

private:
  Vector2D _position;
  unsigned int _width;
  unsigned int _height;

  GLfloat _frameStridew;
  GLfloat _frameStrideh;
  GLfloat _currentFrame;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Texture* _texture;

};

#endif
