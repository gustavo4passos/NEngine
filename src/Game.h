#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "AudioDevice.h"

class Game
{
public:
  // Creates the OpenGL context, open the audio device
  Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion = 3, unsigned int glMinorVersion = 2, bool fullscreen = false, bool vsync = false);
  ~Game();

  // Starts the game loop
  void run();
  // Cleans everything
  void close();

private:
  void handleInput();
  void update();
  void draw();

  GraphicsDevice* _graphicsDevice;
  AudioDevice* _audioDevice;

  bool _running;
};

#endif
