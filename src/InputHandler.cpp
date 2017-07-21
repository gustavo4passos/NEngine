#include "InputHandler.h"
#include <SDL2/SDL.h>

// Create the only instance
InputHandler* InputHandler::_instance = 0;

InputHandler::InputHandler()
{
  _closedWindow = false;
  _keyboardState = 0;
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
}
