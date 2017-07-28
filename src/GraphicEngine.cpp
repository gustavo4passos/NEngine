#include "GraphicEngine.h"
#include "Shader.h"
#include "Texture.h"
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

void GraphicEngine::drawElements(GLuint vao, Texture* texture, GLuint first, GLuint count)
{
  if(texture->id() != _currentTexture)
  {
    texture->use();
    _currentTexture = texture->id();
  }

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
