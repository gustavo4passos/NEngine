#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "GraphicsDevice.h"

class Shader;
class Texture;
class Vector2D;
class Shader;

// The Graphic Engine is a singleton responsible for storing textures and drawing
class GraphicEngine
{
public:
  static GraphicEngine* instance()
  {
    if(_instance == NULL)
    {
      _instance = new GraphicEngine();
    }
    return _instance;
  }
  void draw(GLuint vao, Texture* texture, GLuint first = 0, GLuint count = 6);
  void drawFan(GLuint vao, Texture* texture, GLuint first = 0, GLuint count = 4);
  void drawFan(GLuint vao, Texture* texture, const Vector2D* position, GLuint first = 0, GLuint count = 4);
  void drawElements(GLuint vao, Texture* texture, GLuint first = 0, GLuint count = 4);

  void useShader(Shader* shader);

private:
  // Define only instance
  static GraphicEngine* _instance;

  GraphicEngine();
  void useProgram(Shader shader);
  Shader* _currentShader;
  GLuint _currentTexture;
};

#endif
