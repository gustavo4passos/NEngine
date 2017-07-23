#include "GraphicEngine.h"
#include "Shader.h"

//Create the only instance
GraphicEngine* GraphicEngine::_instance = NULL;

GraphicEngine::GraphicEngine()
{
  _currentShader = 0;
}

void GraphicEngine::draw(GLuint vao, Shader* shader, GLuint count)
{
  if(shader->shaderID() != _currentShader)
  {
    glUseProgram(shader->shaderID());
    _currentShader = shader->shaderID();
  }
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, count);
}

void GraphicEngine::drawElements(GLuint vao, const Shader* shader, int count)
{
  if(shader->shaderID() != _currentShader)
  {
    glUseProgram(shader->shaderID());
    _currentShader = shader->shaderID();
  }
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}
