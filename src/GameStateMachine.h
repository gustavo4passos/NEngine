#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <vector>

class GameState;

// The Game State Machine is responsible for handling game states, including rendering, updating, and ending them
// The games states are arranged in a stack, with the last on in the queue being the one active
// When a new state starts, it pushed to the end of the stack, and remains there until it`s popped, and the previous state is then run (if there was a previous)
class GameStateMachine
{
public:
  GameStateMachine() {}

  // Updates and draw the current game state
  void update(unsigned gameTime);
  void draw();

  // Push a game state into the back of the stack and start it
  void pushState(GameState* gameState);
  void popState();

  void close();


private:
  std::vector<GameState*> _gameStates;
};

#endif
