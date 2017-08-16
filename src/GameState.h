#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <string>

class GameState
{
public:
  GameState() { /* empty */ }

  // Loads necessary assets
  virtual void start() { /* empty */ }
  // Cleans memory and uload data before closing
  virtual void end() { /* empty */ }

  virtual void handleInput() { /* empty */ }
  virtual void update(unsigned int gameTime){ /* empty */ }
  virtual void draw() { /* empty */ }

  // Getters
  std::string stateName() const { return _stateName; }

private:
  // The name of the state
  // Ex: main menu, pause menu, play menu
  std::string _stateName;
};

#endif
