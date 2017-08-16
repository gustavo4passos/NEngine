#include "Game.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "AudioEngine.h"
#include "Background.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "MapGameState.h"
#include "GraphicEngine.h"
#include "Player.h"
#include "InputHandler.h"
#include "Layer.h"
#include "Loader.h"
#include "PhysicsEngine.h"
#include "Shader.h"
#include "Camera.h"
#include "World.h"

// Delete me
#include <math.h>


Game::Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion, unsigned int glMinorVersion, bool fullscreen, bool vsync, bool transparency)
{
  _graphicsDevice = new GraphicsDevice(windowTitle, windowWidth, windowHeight, glMajorVersion, glMinorVersion, fullscreen, vsync, transparency);
  _graphicsDevice->clearColor(0.f, 0.f, 0.f, 1.f);
  _audioDevice = new AudioDevice();
  _gameStateMachine = new GameStateMachine();

  // Load orthographic matrix
  GraphicEngine::instance()->setUpOrtographicMatrix(_graphicsDevice->windowWidth(), _graphicsDevice->windowHeight());
  // Inform the camera about the screen resolution
  Camera::instance()->setScreenResolution(_graphicsDevice->windowWidth(), _graphicsDevice->windowHeight());

  defaultShader = new Shader("../shaders/sprite_render.vs", "../shaders/sprite_render.fs");
  staticShader = new Shader("../shaders/sprite_static.vs", "../shaders/sprite_static.fs");

  _gameStateMachine->pushState(new MapGameState("../data/loaddata.xml"));
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
  // Toggles fullscreen with ALT ENTER
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_LALT) && InputHandler::instance()->keyDown(SDL_SCANCODE_RETURN)) _graphicsDevice->toggleFullscreen();
  // Toggles vsync with V
  if(InputHandler::instance()->keyUp(SDL_SCANCODE_V)) _graphicsDevice->toggleVsync();
  if(InputHandler::instance()->closedWindow()) _running = false;
}

void Game::update(unsigned int gameTime)
{
  _gameStateMachine->update(gameTime);
}

void Game::draw()
{
  // Clear the color buffer
  _graphicsDevice->clear();

  _gameStateMachine->draw();

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
  _gameStateMachine->close();

  // Close graphics device
  _graphicsDevice->checkForErrors();
  _graphicsDevice->close();
  delete _graphicsDevice;
  _graphicsDevice = NULL;

  // Close audio device
  AudioEngine::instance()->clean();
  _audioDevice->checkForErrors();
  _audioDevice->close();
  delete _audioDevice;
  _audioDevice = NULL;
}
