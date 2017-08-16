#include "GameStateMachine.h"

#include <stdio.h>
#include "MapGameState.h"
#include "InputHandler.h"
#include "Shader.h"

void GameStateMachine::update(unsigned gameTime)
{
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_K))
  {
    popState();
  }
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_O) &&
     InputHandler::instance()->keyDown(SDL_SCANCODE_P))
   {
     pushState(new MapGameState("../data/loaddata.xml"));
   }
  if(!_gameStates.empty())
  {
    _gameStates.back()->update(gameTime);
  }
  else
  {
    printf("GAME STATE MACHINE ERROR: Can't update Game State: There are no active game states.\n");
  }
}

void GameStateMachine::draw()
{
  if(!_gameStates.empty())
  {
    _gameStates.back()->draw();
  }
  else
  {
    printf("GAME STATE MACHINE ERROR: Can't draw Game state: There are no active Game State.\n");
  }
}

void GameStateMachine::pushState(GameState* gameState)
{
  _gameStates.push_back(gameState);
  _gameStates.back()->start();
}

void GameStateMachine::popState()
{
  if(!_gameStates.empty())
  {
    _gameStates.back()->end();
    delete _gameStates.back();
    _gameStates.back() = NULL;
    _gameStates.pop_back();
  }
  else
  {
    printf("GAME STATE MACHINE ERROR: Unable to pop state: There are no active Game State.\n");
  }
}

void GameStateMachine::close()
{
  while(!_gameStates.empty())
  {
    _gameStates.back()->end();
    delete _gameStates.back();
    _gameStates.back() = NULL;
    _gameStates.pop_back();
  }
}
