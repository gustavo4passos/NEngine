#include "Layer.h"
#include "GraphicEngine.h"

Layer::Layer(unsigned width, unsigned height, const char* name, GLuint vao, GLuint vbo, GLuint ebo, unsigned indexCount)
: _width(width), _height(height), _name(name), _vao(vao), _vbo(vbo), _ebo(vbo), _indexCount(indexCount)
{}

void Layer::draw()
{
  GraphicEngine::instance()->drawElements(_vao, _indexCount);
}
