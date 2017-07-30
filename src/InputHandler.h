#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdio.h>
#include <SDL2/SDl.h>
#include "../util/Vector2D.h"

class InputHandler
{
public:
  static InputHandler* instance()
  {
    if(_instance == 0)
    {
      _instance = new InputHandler();
    }
    return _instance;
  }

  // Receive input
  void update();

  // Check for input
  bool closedWindow();
  bool keyDown(SDL_Scancode key) const;
  bool keyUp(SDL_Scancode key) const;
  Vector2D mousePos() const { return _mousePos; }

private:
  InputHandler();
  ~InputHandler();
  static InputHandler* _instance;

  // Current map of the keyboard state
  // Toggle between the 2 to get the previous and current state;
  const Uint8* _keyboardState;
  bool _keyUp[100];

  Vector2D _mousePos;

  // Check if the window clicked on the close window button
  bool _closedWindow;
};

#endif
