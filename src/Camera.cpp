#include "Camera.h"
#include "../util/Vector2D.h"

Camera* Camera::_instance = 0;

Camera::Camera() : _position(Vector2D(0.f, 0.f)), _velocity(Vector2D(0.f, 0.f)), _followPosition(Vector2D(0.f, 0.f)), _screenCenter(Vector2D(0, 0))
{
}

void Camera::setScreenLimits(int top, int right, int bottom, int left, float centerx, float centery)
{
  _topLimit = top;
  _rightLimit = right;
  _bottomLimit = bottom;
  _leftLimit = left;
  _screenCenter = Vector2D(centerx, centery);
}

void Camera::followPosition(Vector2D position)
{
  _followPosition = position - _screenCenter;
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
