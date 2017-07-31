#include "Hero.h"
#include <vector>
#include "Camera.h"
#include "GraphicEngine.h"
#include "InputHandler.h"
#include "PhysicsEngine.h"
#include "World.h"

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

  // Set up collision box
  _collisionBox.x = _position.x();
  _collisionBox.y = _position.y();
  _collisionBox.right = _position.x() + _width;
  _collisionBox.bottom = _position.y() + _height;
  _collisionBox.width = _width;
  _collisionBox.height = _height;
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

  // Create a ghost in the new posisble position to check for collision
  Vector2D tempPosition = _position + _currentVelocity;
  // Make the box smaller than the character
  int offsetx, offsety, widthReducer, heightReducer;
  offsetx = 40;
  offsety = 90;
  widthReducer = 50;
  heightReducer = 0;
  Box tempBox = { 0, tempPosition.x() + offsetx, tempPosition.y() + offsety, (tempPosition.x() + _collisionBox.width) - widthReducer,
                  (tempPosition.y() + _collisionBox.height) - heightReducer, _collisionBox.width, _collisionBox.height };
  // If no collision is found, update the player postition to the new one
  if(!PhysicsEngine::instance()->checkCollisionWithWorld(tempBox))
  {
    _position += _currentVelocity;
    updateCollisionBox();
  }

  // Update camera follow coordinates
  Camera::instance()->followPosition(_position);
}

void Hero::updateCollisionBox()
{
  _collisionBox.x = _position.x();
  _collisionBox.y = _position.y();
  _collisionBox.right = _collisionBox.x + _collisionBox.width;
  _collisionBox.bottom = _collisionBox.y + _collisionBox.height;
}

void Hero::update(unsigned int gameTime)
{
  handleInput();
  animation(gameTime);
  move(gameTime);
  updateCollisionBox();
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
