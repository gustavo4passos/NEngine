#include "Game.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "AudioEngine.h"
#include "Background.h"
#include "GraphicEngine.h"
#include "Hero.h"
#include "InputHandler.h"
#include "Layer.h"
#include "Loader.h"
#include "Shader.h"
#include "Tileset.h"
#include "Texture.h"
#include "World.h"

Game::Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion, unsigned int glMinorVersion, bool fullscreen, bool vsync, bool transparency)
{
  _graphicsDevice = new GraphicsDevice(windowTitle, windowWidth, windowHeight, glMajorVersion, glMinorVersion, fullscreen, vsync, transparency);
  _graphicsDevice->clearColor(0.f, 0.f, 0.f, 1.f);
  // Hide cursor
  _graphicsDevice->showCursor(false);
  _audioDevice = new AudioDevice();

  defaultShader = new Shader("../shaders/sprite_render.vs", "../shaders/sprite_render.fs");
  staticShader = new Shader("../shaders/sprite_static.vs", "../shaders/sprite_static.fs");

  _hero = Loader::instance()->loadHero("../data/loaddata.xml", defaultShader);
  _world = Loader::instance()->loadWorld("../resources/tmx/seiken.tmx", staticShader);

  // Set orthographic matrix
  ortho = glm::ortho(0.f, float(_graphicsDevice->windowWidth()), float(_graphicsDevice->windowHeight()), 0.f);

  int audio = AudioEngine::instance()->loadWAV("../resources/audio/background/northern_wind.wav", true, 16);
  int source = AudioEngine::instance()->createSource();
  AudioEngine::instance()->play(source, audio);

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

void Game::update(unsigned int GameTime)
{
  _hero->update(GameTime);
}

void Game::draw()
{
  _graphicsDevice->clear();

  // Binds static shader and draw everything static
  GraphicEngine::instance()->useShader(staticShader);
  staticShader->setMat4("ortho", glm::value_ptr(ortho));
  _world->draw();

  // Binds default shader and draw game objects
  GraphicEngine::instance()->useShader(defaultShader);
  defaultShader->setMat4("ortho", glm::value_ptr(ortho));

  _hero->draw();

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
  delete _hero;
  delete _world;

  _hero = NULL;
  _world = NULL;

  _graphicsDevice->checkForErrors();
  _graphicsDevice->close();
}
