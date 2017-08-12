#include "Camera.h"
#include "GraphicEngine.h"
#include "Shader.h"
#include "Texture.h"
#include "World.h"
#include "../util/Vector2D.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

//Create the only instance
GraphicEngine* GraphicEngine::_instance = NULL;

GraphicEngine::GraphicEngine()
{
  // Set the current texture and shader to 0
  _currentShader = NULL;
  _currentTexture = 0;

  // Load generic shaders
  _boxShader = new Shader("../shaders/boxshader.vs", "../shaders/boxshader.fs");
}

void GraphicEngine::setUpOrtographicMatrix(GLfloat windowWidth, GLfloat windowHeight)
{
  ortho = glm::ortho(0.f, windowWidth, windowHeight, 0.f);
}

// Uses the current ortographic matrix in the CURRENT SHADER
// The shader binding is not done inside the method so the caller can optimize various draw calls using the same matrix
void GraphicEngine::useOrtographicMatrix()
{
  _currentShader->setMat4("ortho", glm::value_ptr(ortho));
}

void GraphicEngine::draw(GLuint vao, Texture* texture, GLuint first, GLuint count)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, first, count);
}

void GraphicEngine::drawFan(GLuint vao, Texture* texture)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

// Draw sprite in a certain position, stored in a Vector2D
void GraphicEngine::drawFan(GLuint vao, Texture* texture, const Vector2D* position)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }

  glBindVertexArray(vao);

  glm::mat4 translate;
  translate = glm::translate(translate, glm::vec3(position->x(), position->y(), 0.f));

  if(_currentShader != NULL) _currentShader->setMat4("transform", glm::value_ptr(translate));
  else
  {
    printf("GRAPHIC ENGINE ERROR: Can't draw sprite. The current shader is NULL.");
  }
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GraphicEngine::drawFrame(GLuint vao, Texture* texture, const Vector2D* position, float currentFramex, float currentFramey)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }

  glBindVertexArray(vao);

  glm::mat4 translate;
  translate = glm::translate(translate, glm::vec3(position->x(), position->y(), 0.f));

  if(_currentShader != NULL)
  {
    _currentShader->setMat4("transform", glm::value_ptr(translate));
    GLfloat frames[2] = { currentFramex, currentFramey };
    _currentShader->setUniform2fv("currentFrame", frames);
  }
  else
  {
    printf("GRAPHIC ENGINE ERROR: Can't draw sprite. The current shader is NULL.");
  }
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GraphicEngine::drawElements(GLuint vao, Texture* texture, GLuint count)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}

void GraphicEngine::drawElements(GLuint vao, GLuint count)
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}

void GraphicEngine::useShader(Shader* shader)
{
  if(_currentShader == NULL)
  {
      shader->use();
      _currentShader = shader;
  }
  else
  {
    if(_currentShader->id() != shader->id())
    {
      shader->use();
      _currentShader = shader;
    }
  }
}

void GraphicEngine::useTexture(Texture* texture)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }
}

// Gen and binds vertex array object
GLuint GraphicEngine::loadVao()
{
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Check for errors
  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    printf("GRAPHIC ENGINE ERROR: Unable to load vertex array object. Error: %s\n", gluErrorString(error));
  }
  return vao;
}

// Gen and binds vertex buffer object
GLuint GraphicEngine::loadToVbo(GLfloat data[], GLsizeiptr bytes)
{
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);

  // Check for errors
  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    printf("GRAPHIC ENGINE ERROR: Unable to load vertex buffer object. Error: %s\n", gluErrorString(error));
  }

  return vbo;
}

GLuint GraphicEngine::loadToEbo(GLuint data[], GLsizeiptr bytes)
{
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);

  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    printf("GRAPHIC ENGINE ERROR: Unable to load element array object. Error: %s\n", gluErrorString(error));
  }

  return ebo;
}

// Draw a box in the screen
// ATTENTION
// This method is highly inneficient and should only be used for debugging purposes
void GraphicEngine::drawBox(Box box, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  // Generate temprary vao to draw box;
  GLuint vao, vbo;
  vao = loadVao();

  // Generate box vbo data
  GLfloat vertices[] =
  {
    box.x, box.y,
    box.right, box.y,
    box.right, box.bottom,
    box.x, box.bottom
  };

  // Load data into memory
  vbo = loadToVbo(vertices, sizeof(vertices));
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Link data to box shader
  this->useShader(this->_boxShader);
  this->_boxShader->vertexAttribPointer("position", 2, 0, 0);
  this->_boxShader->setUniform4f("rectColor", r, g, b, a);

  this->useOrtographicMatrix();
  printf("GRAPHIC ENGINE ERROR: DRAW BOX METHOD: Fix camera issue!\n");
  glm::mat4 camera = glm::translate(glm::mat4(), glm::vec3(Camera::instance()->x(), Camera::instance()->y(), 0.f));
  _currentShader->setMat4("camera", glm::value_ptr(camera));

  // Draw
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  // Delete buffers
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
