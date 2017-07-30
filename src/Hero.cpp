#include "Hero.h"
#include <vector>
#include "GraphicEngine.h"
#include "InputHandler.h"

Hero::Hero(const char* textureFilePath, int x, int y, int width, int height, float speed,  Shader* shader, float framesx, float framesy)
: _width(width), _height(height), _speed(speed), _framesx(framesx), _framesy(framesy), _position(Vector2D(x, y)), _velocity(Vector2D(0.f, 0.f)), _currentVelocity(0.f, 0.f)
{
  _texture = new Texture(textureFilePath);

  // If the width and height arguments are 0, set the dimensions of the hero to be the texture dimensions
  if(_width == 0 || _height == 0)
  {
    _width =  _texture->width();
    _height = _texture->height();
  }

  // Set the initial frame as 1
  _currentFramex = 0;
  _currentFramey = 0;

  // Starts the time keeper as 0
  _timeKeeper = 0;

  // Transition speed to get to desired speed
  _transitionSpeed = 0.015;

  // Get the tex stride for each frame
  _frameStridew = ((_texture->width() / framesx) / _texture->width());
  _frameStrideh = (_texture->height() / framesy) / _texture->height();

  GLfloat vertices[] =
  {  // Quad vertices          |  TexCoordinates
     0.f         , 0.f          , 0.f                            , 0.f,
     _width * 1.f, 0.f          , _frameStridew,              0.f,
     _width * 1.f, _height * 1.f, _frameStridew,   _frameStrideh,
    0.f          , _height * 1.f, 0.f                           , _frameStrideh
  };

  _vao = GraphicEngine::instance()->loadVao();
  _vbo = GraphicEngine::instance()->loadToVbo(vertices, sizeof(vertices));

  shader->vertexAttribPointer("position", 2, 4, 0);
  shader->vertexAttribPointer("texcoord", 2, 4, 2);
}

void Hero::handleInput()
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
  if(InputHandler::instance()->keyDown(SDL_SCANCODE_DOWN) && InputHandler::instance()->keyDown(SDL_SCANCODE_UP))
  {
    _velocity.setY(0);
  }
}

void Hero::animation(unsigned int gameTime)
{
    // Animate walk cycle if moving
    if(_velocity.length() > 0)
    {
      _currentFramex = (int(gameTime / 100.f) % _framesx) * _frameStridew;
    }
    else
    {
      _currentFramex = 0;
    }

    // Checks which direction the character is facing, and chooses frame accordingly
    if(_velocity.x() < 0)
    {
      _currentFramey = 1.f / _framesy;
    }
    if(_velocity.x() > 0)
    {
      _currentFramey = 3.f / _framesy;
    }
    if(_velocity.y() < 0)
    {
      _currentFramey = 0.f / _framesy;
    }
    if(_velocity.y() > 0)
    {
      _currentFramey = 2.f / _framesy;
    }
}

void Hero::move(unsigned int gameTime)
{
  unsigned int timeDifference = gameTime - _timeKeeper;
  _currentVelocity.setX(_currentVelocity.x() * (1 - timeDifference * _transitionSpeed) + _velocity.x() * (timeDifference * _transitionSpeed));
  _currentVelocity.setY(_currentVelocity.y() * (1 - timeDifference * _transitionSpeed) + _velocity.y() * (timeDifference * _transitionSpeed));
  _position += _currentVelocity;
}

void Hero::update(unsigned int gameTime)
{
  handleInput();
  animation(gameTime);
  move(gameTime);

  _timeKeeper = gameTime;
}


void Hero::draw()
{
  GraphicEngine::instance()->drawFrame(_vao, _texture, &_position, _currentFramex, _currentFramey);
}

Hero::~Hero()
{
  delete _texture;
  _texture = NULL;

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}
