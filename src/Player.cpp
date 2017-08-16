#include "Player.h"
#include <vector>
#include "Camera.h"
#include "GraphicEngine.h"
#include "InputHandler.h"
#include "PhysicsEngine.h"
#include "World.h"

Player::Player(const char* textureFilePath, int x, int y, int width, int height, float speed, float framesx, float framesy)
: _width(width), _height(height), _speed(speed), _framesx(framesx), _framesy(framesy), _position(Vector2D(x, y)), _velocity(Vector2D(0.f, 0.f)), _currentVelocity(0.f, 0.f)
{
  _texture = new Texture(textureFilePath);

  // If the width and height arguments are 0, set the dimensions of the player to be the texture dimensions
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
  _transitionSpeed = 0.30;

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

  GraphicEngine::instance()->defaultShader()->vertexAttribPointer("position", 2, 4, 0);
  GraphicEngine::instance()->defaultShader()->vertexAttribPointer("texcoord", 2, 4, 2);

  // Make the box smaller than the character (!!FIXME)
  int offsetx, offsety, widthReducer, heightReducer;
  offsetx = 40;
  offsety = 40;
  widthReducer = 80;
  heightReducer = 70;

  // Set up collision box
  _collisionBox.x = _position.x() + offsetx;
  _collisionBox.y = _position.y() + offsety;
  _collisionBox.width = _width - widthReducer;
  _collisionBox.height = _height - heightReducer;
  _collisionBox.right = _position.x() + _width;
  _collisionBox.bottom = _position.y() + _height;

}

void Player::handleInput()
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

void Player::animation(unsigned int gameTime)
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

void Player::move(unsigned int gameTime)
{
  // Time difference between the current and previous frame
  unsigned int timeDifference = gameTime - _timeKeeper;

  // Accelerates smoothly
  _currentVelocity.setX(_transitionSpeed * _velocity.x() + (1 - _transitionSpeed) * _currentVelocity.x());
  _currentVelocity.setY(_transitionSpeed * _velocity.y() + (1 - _transitionSpeed) * _currentVelocity.y());

  // Create a ghost in the new posisble position to check for collision
  // Vector2D tempPosition = _position + _currentVelocity;
  Box tempBox = { 0, _collisionBox.x, _collisionBox.y, _collisionBox.right, _collisionBox.bottom, _collisionBox.width, _collisionBox.height };
  tempBox.x += _currentVelocity.x();
  tempBox.right += _currentVelocity.x();
  tempBox.y += _currentVelocity.y();
  tempBox.bottom += _currentVelocity.y();

  Vector2D tempPosition = PhysicsEngine::instance()->detectCollision(_collisionBox, tempBox);
  _collisionBox.x = tempPosition.x();
  _collisionBox.right = tempPosition.x() + _collisionBox.width;
  _collisionBox.y = tempPosition.y();
  _collisionBox.bottom = tempPosition.y() + _collisionBox.height;

  // Make the box smaller than the character (!!FIXME)
  int offsetx, offsety, widthReducer, heightReducer;
  offsetx = 40;
  offsety = 70;

  _position.setX(_collisionBox.x - offsetx);
  _position.setY(_collisionBox.y - offsety);

  // Update camera follow coordinates
  Camera::instance()->followPosition(_position);
}


void Player::update(unsigned int gameTime)
{
  handleInput();
  animation(gameTime);
  move(gameTime);
  _timeKeeper = gameTime;
}


void Player::draw()
{
  GraphicEngine::instance()->useDefaultShader();
  GraphicEngine::instance()->useOrtographicMatrix();
  GraphicEngine::instance()->useCamera();
  GraphicEngine::instance()->drawFrame(_vao, _texture, &_position, _currentFramex, _currentFramey);
}

Player::~Player()
{
  delete _texture;
  _texture = NULL;

  GraphicEngine::instance()->deleteVbo(&_vbo);
  GraphicEngine::instance()->deleteEbo(&_ebo);
  GraphicEngine::instance()->deleteVao(&_vao);
}
