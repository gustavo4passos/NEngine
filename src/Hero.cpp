#include "Hero.h"
#include "GraphicEngine.h"
#include "InputHandler.h"

Hero::Hero(const char* textureFilePath, int x, int y, int width, int height, float speed,  Shader* shader, float framesw, float framesh)
: _width(width), _height(height), _speed(speed), _position(Vector2D(x, y)), _velocity(Vector2D(0.f, 0.f))
{
  _texture = new Texture(textureFilePath);

  // If the width and height arguments are 0, set the dimensions of the hero to be the texture dimensions
  if(_width == 0 || _height == 0)
  {
    _width =  _texture->width();
    _height = _texture->height();
  }

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  GLfloat vertices[] =
  {  // Quad vertices         |  TexCoordinates
     0.f        , 0.f         , 0.f                                            , 0.f,
     _width * 1.f, 0.f         , ((_texture->width() / framesw) / _texture->width()), 0.f,
     _width * 1.f, _height * 1.f, (_texture->width() / framesw) / _texture->width(), (_texture->height() / framesh) / _texture->height(),
    0.f        , _height * 1.f, 0.f                                            , (_texture->height() / framesh) / _texture->height()
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  shader->vertexAttribPointer("position", 2, 4, 0);
  shader->vertexAttribPointer("texcoord", 2, 4, 2);
}

void Hero::update(unsigned int gameTime)
{
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_LEFT))
  {
    _velocity.setX(-_speed);
  }
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_RIGHT))
  {
    _velocity.setX(_speed);
  }
  if(!(InputHandler::instance()->keyDown(SDL_SCANCODE_LEFT)) && !(InputHandler::instance()->keyDown(SDL_SCANCODE_RIGHT)))
  {
    _velocity.setX(0);
  }
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_LEFT) && InputHandler::instance()->keyDown(SDL_SCANCODE_RIGHT))
  {
    _velocity.setX(0);
  }
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_UP))
  {
    _velocity.setY(-_speed);
  }
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_DOWN))
  {
    _velocity.setY(_speed);
  }
  if(!(InputHandler::instance()->keyDown(SDL_SCANCODE_DOWN)) && !(InputHandler::instance()->keyDown(SDL_SCANCODE_UP)))
  {
    _velocity.setY(0);
  }

  _position += _velocity;
}

void Hero::draw()
{
  GraphicEngine::instance()->drawFan(_vao, _texture, &_position);
}
