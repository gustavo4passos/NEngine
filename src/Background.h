#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"

class Game;

class Background : public GameObject
{
public:
  Background(const char* imageFile, Shader* shader, int width = 0, int height = 0);
  ~Background();

  friend class Game;

  virtual void draw();
  virtual void update(unsigned int GameTime){}
};

#endif
