#ifndef CAMERA_H
#define CAMERA_H

#include "GraphicEngine.h"
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
  const GLfloat* transformationMatrix() const { return glm::value_ptr(_transformationMatrix); }

  void followPosition(Vector2D position);
  void update();
  void setScreenResolution(int width, int height) { _screenWidth = width; _screenHeight = height; }
  void setMapLimits(int left, int right, int top, int bottom);
  void focusAt(int x, int y, int objectWidth, int objectHeight);

private:
  static Camera* _instance;

  // Screen info
  int _screenWidth;
  int _screenHeight;

  // Camera position
  Vector2D _position;
  Vector2D _velocity;
  Vector2D _currentVelocity;
  Vector2D _followPosition;
  float _weightedAcceleration;
  glm::mat4 _transformationMatrix;

  // Screen limits (in pixels)
  Vector2D _screenCenter;
  int _topLimit;
  int _rightLimit;
  int _bottomLimit;
  int _leftLimit;
};

#endif
