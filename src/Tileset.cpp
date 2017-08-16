#include "Tileset.h"
#include "Texture.h"
#include "GraphicEngine.h"

Tileset::Tileset(const char* path, const char* name, unsigned width, unsigned height, unsigned tileWidth, unsigned tileHeight, unsigned columns)
  : _name(name), _width(width), _height(height), _tileWidth(tileWidth), _tileHeight(tileHeight), _columns(columns)
{
  _rows = height / tileHeight;
  _texture = new Texture(path);
}

void Tileset::use()
{
  // IMPORTANT: Always request the graphic engine to use textures and shaders
  GraphicEngine::instance()->useTexture(_texture);
}

Tileset::~Tileset()
{

  delete _texture;
  _texture = NULL;
}
