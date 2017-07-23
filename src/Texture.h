#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "GraphicsDevice.h"

class Texture
{
public:
  Texture(std::string internalFormatName, std::string formatName, int width, int height, const GLvoid* pixels, bool linearFiltering = false, bool mirrorRepeat = false);
  GLuint id() const { return _id; }

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