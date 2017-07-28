#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "GraphicsDevice.h"

class Texture
{
public:
  Texture(std::string path, bool linearFiltering = false, bool mirrorRepeat = false);
  ~Texture();
  GLuint id() const { return _id; }
  int width() const { return _width; }
  int height() const { return _height; }

  // Binds texture to the current context
  void use();

private:
  // Texture dimensions
  int _width;
  int _height;

  // Object ID in the GPU
  GLuint _id;

  std::string _internalFormat;
  std::string _format;

};

#endif
