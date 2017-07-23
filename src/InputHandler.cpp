#include <SDL2/SDL.h>
#include "InputHandler.h"

// Create the only instance
InputHandler* InputHandler::_instance = 0;

InputHandler::InputHandler()
{
  _closedWindow = false;
  _keyboardState = 0;

  // Initialize keyboard map as false for keyup test
  for(int i = 0; i < 500; i++)
  {
    _keyUp[100] = false;
  }
}

InputHandler::~InputHandler()
{
  delete _keyboardState;
}

// Check for input
void InputHandler::update()
{
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0)
  {
    if(e.type == SDL_QUIT)
    {
      _closedWindow = true;
    }
    if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
    {
    _keyUp[SDL_SCANCODE_ESCAPE] = true;
    }
    else
    {
      _keyUp[SDL_SCANCODE_ESCAPE] = false;
    }
    if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F5)
    {
    _keyUp[SDL_SCANCODE_F5] = true;
    }
    else
    {
      _keyUp[SDL_SCANCODE_F5] = false;
    }
  }

  // Store the kebyaord state at the moment
  _keyboardState = SDL_GetKeyboardState(0);
}

bool InputHandler::closedWindow()
{
  if(_closedWindow)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool InputHandler::keyDown(SDL_Scancode key) const
{
  if(_keyboardState[key])
  {
    return true;
  }
  return false;
}

bool InputHandler::keyUp(SDL_Scancode key) const
{
  if(_keyUp[key])
  {
    return true;
  }
  return false;
}
