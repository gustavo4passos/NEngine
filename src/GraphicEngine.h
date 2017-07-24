#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "GraphicsDevice.h"

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
  void draw(GLuint vao, Shader* shader, GLuint first = 0, GLuint count = 6);
  void drawElements(GLuint vao, const Shader* shader, int count = 4);

private:
  // Define only instance
  static GraphicEngine* _instance;

  GraphicEngine();
  void useProgram(Shader shader);
  GLuint _currentShader;
};

#endif
