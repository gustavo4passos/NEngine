#include "Game.h"
#include "InputHandler.h"
#include "Shader.h"
#include "AudioEngine.h"
#include "Texture.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "GraphicEngine.h"
#include "Hero.h"
#include <SDL2/SDL.h>

#include <vector>
#include <string>

Game::Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion, unsigned int glMinorVersion, bool fullscreen, bool vsync)
{
  _graphicsDevice = new GraphicsDevice(windowTitle, windowWidth, windowHeight, glMajorVersion, glMinorVersion, fullscreen, vsync);
  _graphicsDevice->clearColor(0.f, 0.f, 0.f, 1.f);

  _audioDevice = new AudioDevice();
}

Game::~Game()
{
  delete _graphicsDevice;
  _graphicsDevice = NULL;

  delete _audioDevice;
  _audioDevice = NULL;
}

void Game::handleInput()
{
  InputHandler::instance()->update();
  if(InputHandler::instance()->keyUp(SDL_SCANCODE_ESCAPE)) _running = false;
  if(InputHandler::instance()->keyUp(SDL_SCANCODE_F5)) _graphicsDevice->toggleFullscreen();
  if(InputHandler::instance()->closedWindow()) _running = false;
}

void Game::update()
{}

void Game::draw()
{
  _graphicsDevice->clear();
  _graphicsDevice->swap();
}

void Game::run()
{
  _running = true;
    while(_running)
    {
    handleInput();
    update();
    draw();
  }
}

void Game::close()
{
  _graphicsDevice->checkForErrors();
  _graphicsDevice->close();
}
