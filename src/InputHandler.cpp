#include <SDL2/SDL.h>
#include "InputHandler.h"

// Create the only instance
InputHandler* InputHandler::_instance = 0;

InputHandler::InputHandler() : _mousePos(0, 0)
{
  // Clears the keyboard
  _keyboardState = 0;

  // Stores if the user tried to close the windows
  _closedWindow = false;
}

InputHandler::~InputHandler()
{
  delete _keyboardState;
}

// Check for input
void InputHandler::update()
{

  // Get mouse position
  int mousex, mousey;
  SDL_GetMouseState(&mousex, &mousey);
  _mousePos.setX(float(mousex));
  _mousePos.setY(float(mousey));

  SDL_Event e;
  while(SDL_PollEvent(&e) != 0)
  {
    if(e.type == SDL_QUIT)
    {
      _closedWindow = true;
    }
  }

  // Store the kebyaord state at the moment
  _keyboardState =  SDL_GetKeyboardState(0);

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
  if(_keyboardState[key])
  {
    return true;
  }
  return false;
}
