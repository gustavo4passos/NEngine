#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Layer;
class Loader;
class Shader;
class Tileset;

class World
{
public:
  World(Tileset* tileset);
  ~World();

  friend class Loader;

  // Draw layers to the screen
  void draw();

private:
  // Storest data with information about the tileset sprite
  Tileset* _tileset;
  // Stores the layers objects
  std::vector<Layer*> _layers;

  // Add layer
  void addLayer(Layer* layer);
};

#endif
