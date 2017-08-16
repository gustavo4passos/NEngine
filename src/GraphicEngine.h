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

  // Load the ortographic and camera matrix to the current shader
  void useOrtographicMatrix();
  void useCamera();

  // Draw methods
  void draw(GLuint vao, Texture* texture, GLuint first = 0, GLuint count = 6);
  void drawFan(GLuint vao, Texture* texture);
  void drawFan(GLuint vao, Texture* texture, const Vector2D* position);
  void drawFrame(GLuint vao, Texture* texture, const Vector2D* position, float currentFramex = 0, float currentFramey = 0);
  void drawElements(GLuint vao, Texture* texture, GLuint count);
  void drawElements(GLuint vao, GLuint count);
  void drawBox(Box box, GLfloat r, GLfloat g, GLfloat b, GLfloat a);


  // Load methods
  GLuint loadVao();
  GLuint loadToVbo(GLfloat data[], GLsizeiptr bytes);
  GLuint loadToEbo(GLuint data[], GLsizeiptr bytes);

  // Clean methods
  void deleteVao(GLuint* vao);
  void deleteVbo(GLuint* vbo);
  void deleteEbo(GLuint* ebo);
  void deleteTexture(GLuint* texture);

  // Select current shader
  void useShader(Shader* shader);
  void useStaticShader();
  void useDefaultShader();

  // Access shader info
  Shader* defaultShader() const { return _defaultShader; }
  Shader* staticShader() const { return _staticShader; }

  // Select current texture
  void useTexture(Texture* texture);

private:
  // Define only instance
  static GraphicEngine* _instance;


  // Transformation matrices
  glm::mat4 ortho;
  glm::mat4 camera;

  // Shaders
  Shader* _defaultShader;
  Shader* _staticShader;
  Shader* _boxShader;

  GraphicEngine();
  void useProgram(Shader shader);

  // Store the current shader and texture to avoid changing the state
  Shader* _currentShader;
  GLuint _currentTexture;
};

#endif
