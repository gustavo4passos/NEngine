#include "World.h"
#include "GraphicEngine.h"
#include "Hero.h"
#include "Layer.h"
#include "Loader.h"
#include "PhysicsEngine.h"
#include "Shader.h"
#include "Texture.h"
#include "Tileset.h"

World::World(Tileset* tileset, int width, int height, int tileWidth, int tileHeight) : _width(width), _height(height), _tileWidth(tileWidth), _tileHeight(tileHeight)
{
  _tileset = tileset;
}

void World::draw()
{
  _tileset->use();
  for(int i = 0; i < _layers.size(); i++)
  {
    _layers[i]->draw();
  }
}

World::~World()
{
  // Clean memory
  delete _tileset;
  _tileset = NULL;

  for(std::vector<Layer*>::iterator it = _layers.begin(); it != _layers.end(); it++)
  {
    delete *it;
    * it = NULL;
  }
}

void World::addLayer(Layer* layer)
{
  _layers.push_back(layer);
}

void World::addCollisionBox(Box box)
{
  _collisionLayer.push_back(box);
}
