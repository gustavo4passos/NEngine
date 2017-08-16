#include "Background.h"
#include "GraphicEngine.h"

Background::Background(const char* imageFile, Shader* shader, int width, int height)
{
  _texture = new Texture(imageFile, true, true);

  _width = width;
  _height = height;

  if(_width == 0 || _height == 0)
  {
    _width =  _texture->width();
    _height = _texture->height();
  }

  GLfloat vertices[] =
  { // Vertices                            Tex coordinates
    0.f   , 0.f    , 0.f, 0.f,
    _width, 0.f    , 1.f, 0.f,
    _width, _height, 1.f, 1.f,
    0.f   , _height, 0.f, 1.f
  };

  _vao = GraphicEngine::instance()->loadVao();
  _vbo = GraphicEngine::instance()->loadToVbo(vertices, sizeof(vertices));

  shader->vertexAttribPointer("position", 2, 4, 0);
  shader->vertexAttribPointer("texcoord", 2, 4, 2);
}

void Background::draw()
{
  GraphicEngine::instance()->drawFan(_vao, _texture);
}

Background::~Background()
{
    delete _texture;
    _texture = NULL;

    GraphicEngine::instance()->deleteVbo(&_vbo);
    GraphicEngine::instance()->deleteEbo(&_ebo);
    GraphicEngine::instance()->deleteVao(&_vao);
}
