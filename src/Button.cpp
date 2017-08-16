#include "Button.h"
#include "GraphicEngine.h"
#include "InputHandler.h"

Button::Button(const char* sprite, int x, int y, int width, int height, int frames) : _position(float(x), float(y)), _width(width), _height(height)
{
  _texture = new Texture(sprite);

  if(width == 0 || height == 0)
  {
    _width = _texture->width();
    _height = _texture->height();
  }
  else
  {
    _width = width;
    _height = height;
  }

  _frameStridew = (float(_texture->width()) / float(frames)) / _texture->width();
  _frameStrideh = 1.f;

  GLfloat vertices[] =
  {
    0.f         , 0.f          , 0.f         , 0.f         ,
    _width * 1.f, 0.f          , _frameStridew, 0.f         ,
    _width * 1.f, _height * 1.f, _frameStridew, _frameStrideh,
    0.f         , _height * 1.f, 0.f         , _frameStrideh
  };

  _vao = GraphicEngine::instance()->loadVao();
  _vbo = GraphicEngine::instance()->loadToVbo(vertices, sizeof(vertices));

  GraphicEngine::instance()->staticShader()->vertexAttribPointer("position", 2, 4, 0);
  GraphicEngine::instance()->staticShader()->vertexAttribPointer("texcoord", 2, 4, 2);
}

Button::~Button()
{
  delete _texture;
  _texture = NULL;
}

void Button::handleInput()
{
  // If hovering the button, change the button style
  if(InputHandler::instance()->mousePos().x() > _position.x()          &&
     InputHandler::instance()->mousePos().x() < _position.x() + _width &&
     InputHandler::instance()->mousePos().y() > _position.y()          &&
     InputHandler::instance()->mousePos().y() < _position.y() + _height  )
   {
     _currentFrame = 1 * _frameStridew;
   }
   else
   {
     _currentFrame = 0.f;
   }
}
void Button::update(unsigned int gameTime)
{
  handleInput();
}

void Button::draw()
{
  GraphicEngine::instance()->useDefaultShader();
  GraphicEngine::instance()->useOrtographicMatrix();
  GraphicEngine::instance()->useCamera();
  GraphicEngine::instance()->drawFrame(_vao, _texture, &_position, _currentFrame, 0.f);
}
