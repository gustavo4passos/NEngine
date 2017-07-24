#include "GraphicEngine.h"
#include "Shader.h"

//Create the only instance
GraphicEngine* GraphicEngine::_instance = NULL;

GraphicEngine::GraphicEngine()
{
  _currentShader = 0;
}

void GraphicEngine::draw(GLuint vao, Shader* shader, GLuint first, GLuint count)
{
  if(shader->id() != _currentShader)
  {
    glUseProgram(shader->id());
    _currentShader = shader->id();
  }
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, first, count);
}

void GraphicEngine::drawElements(GLuint vao, const Shader* shader, int count)
{
  if(shader->id() != _currentShader)
  {
    glUseProgram(shader->id());
    _currentShader = shader->id();
  }
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}
