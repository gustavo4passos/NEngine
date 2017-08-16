#ifndef MAPGAMESTATE_H
#define MAPGAMESTATE_H

#include "GameState.h"

#include <vector>
#include <string>

class Player;
class Shader;
class World;

class MapGameState : public GameState
{
public:
  MapGameState(const char* loadFile);
  virtual void start();
  virtual void end();

  virtual void handleInput();
  virtual void update(unsigned int gameTime);
  virtual void draw();
private:

  // Draw shaders
  Shader* _staticShader;

  Player* _player;
  World* _world;

  // Just for audio test purposes
  int _audio;
  int _source;
};

#endif
