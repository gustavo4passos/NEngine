#include "Camera.h"
#include "../util/Vector2D.h"

Camera* Camera::_instance = 0;

Camera::Camera() : _position(Vector2D(0.f, 0.f)), _velocity(Vector2D(0.f, 0.f)), _followPosition(Vector2D(0.f, 0.f)), _screenCenter(Vector2D(0.f, 0.f)), _currentVelocity(Vector2D(0.f, 0.f))
{
  _weightedAcceleration = 0.15f;
}

void Camera::setMapLimits(int top, int right, int bottom, int left)
{
  _topLimit = top;
  _rightLimit = right - _screenWidth;
  _bottomLimit = bottom - _screenHeight;
  _leftLimit = left;
}

void Camera::focusAt(int x, int y, int objectWidth, int objectHeight)
{
  int newcenterx = (_screenWidth - objectWidth) / 2;
  int newcentery = (_screenHeight - objectHeight) / 2;

  _screenCenter = Vector2D(newcenterx, newcentery);
}

void Camera::followPosition(Vector2D position)
{
  _velocity = (position) - _followPosition - _screenCenter;
  _followPosition += _velocity;
}

void Camera::update()
{
  // Check if we are inside the edges of the screen
  if(_followPosition.x() < 0)
  {
    _followPosition.setX(0);
  }
  else if(_followPosition.x() > _rightLimit)
  {
    _followPosition.setX(_rightLimit);
  }
  if(_followPosition.y() < 0)
  {
    _followPosition.setY(0);
  }
  else if(_followPosition.y() > _bottomLimit)
  {
    _followPosition.setY(_bottomLimit);
  }

  _position.setX(-(_followPosition.x()));
  _position.setY(-(_followPosition.y()));
}
