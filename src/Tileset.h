#ifndef TILESET_H
#define TILESET_H

#include <string>

class Texture;

class Tileset
{
public:
  Tileset(const char* path, const char* name, unsigned width, unsigned height, unsigned tileWidth, unsigned tileHeight, unsigned columns);
  ~Tileset();

  std::string name() const { return _name; }
  unsigned width() const { return _width; }
  unsigned height() const { return _height; }
  unsigned tileWidth() const { return _tileWidth; }
  unsigned tileHeight() const { return _tileHeight; }
  unsigned columns() const { return _columns; }
  unsigned rows() const { return _rows; }

  void use();

private:
  std::string _name;
  unsigned _tileWidth;
  unsigned _tileHeight;
  unsigned _width;
  unsigned _height;
  unsigned _columns;
  unsigned _rows;
  Texture* _texture;
};

#endif
