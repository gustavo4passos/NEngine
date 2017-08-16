#include "MapGameState.h"

#include "AudioEngine.h"
#include "Button.h"
#include "Camera.h"
#include "GraphicEngine.h"
#include "InputHandler.h"
#include "Loader.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Shader.h"
#include "World.h"

MapGameState::MapGameState(const char* loadFile)
{
  _player = Loader::instance()->loadPlayer(loadFile);
  _world = Loader::instance()->loadWorld(loadFile);
  _button = new Button("../resources/sprites/button-test.png", 200, 200, 150, 75, 2);
}

void MapGameState::start()
{
  Camera::instance()->setMapLimits(0, _world->widthInPixels(), _world->heightInPixels(), 0);
  Camera::instance()->focusAt(_player->position().x(), _player->position().y(), _player->width(), _player->height());
  PhysicsEngine::instance()->connectToTheWorld(_world, _player);

  _audio = AudioEngine::instance()->loadWAV("../resources/audio/background/birds_forest.wav", true, 16);
  _source = AudioEngine::instance()->createSource(1.f, 1.f, true);
  AudioEngine::instance()->play(_source, _audio);
}

void MapGameState::end()
{
  AudioEngine::instance()->stop(_source);
  AudioEngine::instance()->deleteBuffer(_audio);
  AudioEngine::instance()->deleteSource(_source);

  delete _player;
  delete _world;

  _player = NULL;
  _world = NULL;
}

void MapGameState::handleInput()
{

}

void MapGameState::update(unsigned int gameTime)
{
  handleInput();
  _player->update(gameTime);
  _button->update(gameTime);
  Camera::instance()->update();
}

void MapGameState::draw()
{

  _world->draw();
  _player->draw();
  _world->drawOverlay();
   _button->draw();
}
