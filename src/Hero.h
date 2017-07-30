#ifndef HERO_H
#define HERO_H

#include "GameObject.h"

class Game;

class Hero : public GameObject
{
public:
  Hero(const char* textureFilePath, int x, int y, int width, int height, float speed, Shader* shader, float framesx = 1, float framesy = 1);
  ~Hero();
  virtual void update(unsigned int gameTime);
  virtual void draw();

  friend class Game;

private:

  void handleInput();
  void move(unsigned int gameTime);
  void animation(unsigned int gameTime);

  unsigned int _width;
  unsigned int _height;

  // Animation variables
  unsigned int _framesx;
  unsigned int _framesy;
  float _currentFramex;
  float _currentFramey;
  float _frameStridew;
  float _frameStrideh;
  unsigned int _timeKeeper;
  float _transitionSpeed;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  Texture* _texture;

  Vector2D _position;
  Vector2D _velocity;
  Vector2D _currentVelocity;
  float _speed;
};

#endif
