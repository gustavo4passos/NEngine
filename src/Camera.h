#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Vector2D.h"

class Camera
{
public:
  static Camera* instance()
  {
    if(_instance == 0)
    {
      _instance = new Camera();
    }

    return _instance;
  }

  Camera();

  Vector2D position() const { return _position; }
  Vector2D velocity() const { return _velocity; }
  float x() const { return _position.x(); }
  float y() const { return _position.y(); }

  void followPosition(Vector2D position);
  void update();
  void setScreenLimits(int left, int right, int top, int bottom, float centerx, float centery);

private:
  static Camera* _instance;

  // Camera position
  Vector2D _position;
  Vector2D _velocity;
  Vector2D _currentVelocity;
  Vector2D _followPosition;
  float _weightedAcceleration;

  // Screen limits (in pixels)
  Vector2D _screenCenter;
  int _topLimit;
  int _rightLimit;
  int _bottomLimit;
  int _leftLimit;
};

#endif
