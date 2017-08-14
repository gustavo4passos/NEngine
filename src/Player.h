#ifndef HERO_H
#define HERO_H

#include "GameObject.h"
#include "World.h"

class Player : public GameObject
{
public:
  // Loads up the player assets
  // textureFilePath: the path of the sprite file
  // x, y: X and y starting position on the map
  // width, height: Width and height of the texture on the screen
  // speed: movement speed ot the player
  // shader: necessary to link vao data
  // framesx: number of x frames in the texture
  // framesy: number of y frames in the texture
  Player(const char* textureFilePath, int x, int y, int width, int height, float speed, Shader* shader, float framesx = 1, float framesy = 1);
  ~Player();
  virtual void update(unsigned int gameTime);
  virtual void draw();

  unsigned width() const { return _width; }
  unsigned height() const { return _height; }
  Vector2D position() const { return _position; }
  Box collisionBox() const { return _collisionBox; }

private:
  // Managers input from the player
  void handleInput();
  void move(unsigned int gameTime);
  // Sets the current frame to be drawn
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

  // Position attributes
  Vector2D _position;
  Vector2D _velocity;
  Vector2D _currentVelocity;
  Box _collisionBox;
  float _speed;
};

#endif
