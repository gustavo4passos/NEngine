#include "Game.h"
#include "InputHandler.h"
#include "Shader.h"
#include "AudioEngine.h"
#include "Texture.h"
#include "GraphicEngine.h"
#include "Hero.h"
#include <SDL2/SDL.h>

#include <vector>
#include <string>

Game::Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion, unsigned int glMinorVersion, bool fullscreen, bool vsync, bool transparency)
{
  _graphicsDevice = new GraphicsDevice(windowTitle, windowWidth, windowHeight, glMajorVersion, glMinorVersion, fullscreen, vsync, transparency);
  _graphicsDevice->clearColor(0.f, 0.f, 0.f, 1.f);
    _audioDevice = new AudioDevice();

  defaultShader = new Shader("../shaders/sprite_render.vs", "../shaders/sprite_render.fs");
  hero = new Hero("../resources/sprites/jumper.png", 50, 50, 40, 40 , 5, defaultShader, 1, 1);

  // Set orthographic matrix
  ortho = glm::ortho(0.f, float(_graphicsDevice->windowWidth()), float(_graphicsDevice->windowHeight()), 0.f);
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

void Game::update(unsigned int GameTime)
{
  hero->update(GameTime);
}

void Game::draw()
{
  GraphicEngine::instance()->useShader(defaultShader);
  defaultShader->setMat4("ortho", glm::value_ptr(ortho));

  _graphicsDevice->clear();

  hero->draw();

  _graphicsDevice->swap();
}

void Game::run()
{
  _running = true;
    while(_running)
    {
      handleInput();
      update(SDL_GetTicks());
      draw();
  }

  close();
}

void Game::close()
{
  _graphicsDevice->checkForErrors();
  _graphicsDevice->close();
}
