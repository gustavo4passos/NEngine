#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Layer;
class Loader;
class Shader;
class Tileset;

struct Box
{
  int id;
  float x;
  float y;
  float right;
  float bottom;
  int width;
  int height;
};

class Player;

class World
{
  // The loader class is declared as friend so it can load layers into our world
  friend class Loader;
  // The physics Engine will check for collision between characters and the world
  friend class PhysicsEngine;

public:
  World(Tileset* tileset, int width, int height, int tileWidth, int tileHeight);
  ~World();

  unsigned width() const { return _width; }
  unsigned height() const { return _height; }
  unsigned tileWidth() const { return _tileWidth; }
  unsigned tileHeight() const { return _tileHeight; }
  unsigned widthInPixels() const { return _tileWidth * _width; }
  unsigned heightInPixels() const { return _tileHeight * _height; }

  // Draw layers to the screen
  void draw();
  void drawOverlay();

private:
  unsigned _width;
  unsigned _height;
  unsigned _tileWidth;
  unsigned _tileHeight;

  // Storest data about the tileset sprite
  Tileset* _tileset;

  // Stores the layers objects
  std::vector<Layer*> _layers;
  // Layers that will cover the characters
  // For a layers to be read as overlay it needs to have a "value" property of "overlay" insisde a properties element
  /* Ex:
    <layer>
      <properties>
        <property name="doesn`t matter" value="overlay"/>
      </properties>
      <data>
      ...
    </layer>*/
  std::vector<Layer*> _overlayLayers;

  std::vector<Box> _collisionLayer;

  // Add layer
  void addLayer(Layer* layer);
  void addOverlayLayer(Layer* layer);
  void addCollisionBox(Box box);
};

#endif
