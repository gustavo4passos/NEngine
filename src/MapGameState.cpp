#include "MapGameState.h"

#include "AudioEngine.h"
#include "Camera.h"
#include "GraphicEngine.h"
#include "InputHandler.h"
#include "Loader.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Shader.h"
#include "World.h"

MapGameState::MapGameState(const char* loadFile, Shader* defaultShader, Shader* staticShader)
{
  _defaultShader = defaultShader;
  _staticShader = staticShader;
  _player = Loader::instance()->loadPlayer(loadFile, defaultShader);
  _world = Loader::instance()->loadWorld(loadFile, staticShader);
}

void MapGameState::start()
{
  Camera::instance()->setMapLimits(0, _world->widthInPixels(), _world->heightInPixels(), 0);
  Camera::instance()->focusAt(_player->position().x(), _player->position().y(), _player->width(), _player->height());
  PhysicsEngine::instance()->connectToTheWorld(_world, _player);

  int audio = AudioEngine::instance()->loadWAV("../resources/audio/background/birds_forest.wav", true, 16);
  int source = AudioEngine::instance()->createSource(1.f, 1.f, true);
  AudioEngine::instance()->play(source, audio);
}

void MapGameState::end()
{
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
  _player->update(gameTime);
  Camera::instance()->update();
}

void MapGameState::draw()
{
  // Updates camera matrix
  glm::mat4 camera = glm::translate(glm::mat4(), glm::vec3(Camera::instance()->x(), Camera::instance()->y(), 0.f));

  GraphicEngine::instance()->useShader(_staticShader);
  GraphicEngine::instance()->useOrtographicMatrix();
  _staticShader->setMat4("camera", glm::value_ptr(camera));
  _world->draw();

  // Binds default shader and draw game objects
  GraphicEngine::instance()->useShader(_defaultShader);
  GraphicEngine::instance()->useOrtographicMatrix();
  _defaultShader->setMat4("camera", glm::value_ptr(camera));

  _player->draw();

  GraphicEngine::instance()->useShader(_staticShader);
  GraphicEngine::instance()->useOrtographicMatrix();
  _staticShader->setMat4("camera", glm::value_ptr(camera));

  _world->drawOverlay();
}
