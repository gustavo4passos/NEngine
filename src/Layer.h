#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "GraphicsDevice.h"

class Layer
{
public:
  Layer(unsigned width, unsigned height, const char* name, GLuint vao, GLuint vbo, GLuint ebo, unsigned indexCount);
  ~Layer();
  void draw();

private:
  unsigned int _width;
  unsigned int _height;
  std::string _name;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  unsigned _indexCount;
};

#endif
