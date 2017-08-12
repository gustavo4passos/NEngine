#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "GraphicsDevice.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

struct Box;
class Shader;
class Texture;
class Vector2D;

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

  // Set up orthographic matrix
  void setUpOrtographicMatrix(GLfloat windowWidth, GLfloat windowHeight);

  // Load the ortographic matrix to the current shader
  void useOrtographicMatrix();

  // Draw methods
  void draw(GLuint vao, Texture* texture, GLuint first = 0, GLuint count = 6);
  void drawFan(GLuint vao, Texture* texture);
  void drawFan(GLuint vao, Texture* texture, const Vector2D* position);
  void drawFrame(GLuint vao, Texture* texture, const Vector2D* position, float currentFramex = 0, float currentFramey = 0);
  void drawElements(GLuint vao, Texture* texture, GLuint count);
  void drawElements(GLuint vao, GLuint count);
  void drawBox(Box box, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

  // Load functions
  GLuint loadVao();
  GLuint loadToVbo(GLfloat data[], GLsizeiptr bytes);
  GLuint loadToEbo(GLuint data[], GLsizeiptr bytes);

  void useShader(Shader* shader);
  void useTexture(Texture* texture);

private:
  // Define only instance
  static GraphicEngine* _instance;

  // Transformation matrices
  glm::mat4 ortho;
  glm::mat4 camera;

  GraphicEngine();
  void useProgram(Shader shader);

  // Store the current shader and texture to avoid changing the state
  Shader* _currentShader;
  GLuint _currentTexture;

  // Shaders used for generic drawing
  Shader* _boxShader;
};

#endif
