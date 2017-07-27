#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "AudioDevice.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

// A temp declaration of our Hero class declared in Hero.h
class Hero;
class Shader;

class Game
{
public:
  // Creates the OpenGL context, open the audio device
  Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion = 3,
     unsigned int glMinorVersion = 2, bool fullscreen = false, bool vsync = false, bool transparency = false);
  ~Game();

  // Starts the game loop
  void run();
  // Cleans everything
  void close();

private:
  void handleInput();
  void update(unsigned int GameTime);
  void draw();

  GraphicsDevice* _graphicsDevice;
  AudioDevice* _audioDevice;

  // Shaders
  Shader* defaultShader;

  // Game characters
  Hero* hero;

  // Matrices
  glm::mat4 ortho;

  bool _running;
};

#endif
