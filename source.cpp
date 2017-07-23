#include <cmath>
#include "src/GraphicsDevice.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/InputHandler.h"
#include "src/GraphicEngine.h"
#include "src/Shader.h"
#include "src/Texture.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** args)
{
<<<<<<< HEAD
  srand(time(NULL));

  GraphicsDevice graphicsDevice("NEngine", 1366, 768, 4, 2, false, true);
=======
  GraphicsDevice graphicsDevice("NEngine", 1366, 768, false, true);
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b

  Shader test("../shaders/vs.vs", "../shaders/fs.fs");

  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  GLfloat vertices[] =
  {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
  };

  GLuint elements[] =
  {
    1, 2, 3
  };

  SDL_Surface* surf = SDL_LoadBMP("../resources/sprites/img.bmp");
  printf("Texture x and w %i and %i\n", surf->w, surf->h);
<<<<<<< HEAD
  Texture textureTest = Texture("RGB", "RGB", surf->w, surf->h, surf->pixels, true);
=======
  Texture textureTest = Texture("RGB", "RGB", surf->w, surf->h, surf->pixels);
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b

  SDL_FreeSurface(surf);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  test.use();

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "position"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, 0);
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "position"));

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "color"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 5));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "color"));

<<<<<<< HEAD
  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "texcoord"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 6));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "texcoord"));

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "normal"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 8));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "normal"));
=======
  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "texcoord"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "texcoord"));
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b

  int major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  printf("OpenGL version: %i.%i\n", major, minor);

  glVertexAttribPointer(5, 2,  GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
  glEnableVertexAttribArray(5);
  GLenum error = glGetError();
  if(error != GL_NO_ERROR) printf("%s", gluErrorString(error));

  float followmouse = 0;
  float timedelta = 0, lasttick = 0;
<<<<<<< HEAD
  float count = 1;
=======
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b

  bool running = true;
  while(running)
  {
    InputHandler::instance()->update();
    if(InputHandler::instance()->keyUp(SDL_SCANCODE_ESCAPE)) running = false;
    if(InputHandler::instance()->keyUp(SDL_SCANCODE_F5)) graphicsDevice.toggleFullscreen();
    if(InputHandler::instance()->closedWindow()) running = false;

    int x, y;
    SDL_GetMouseState(&x, &y);

    glm::mat4 view = glm::lookAt(
    glm::vec3(1.2f, 2.2f, 1.2f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
    );

    glEnable(GL_DEPTH_TEST);
    glm::mat4 proj = glm::perspective(glm::radians(y * 0.5f), 1366 / 768.f, 1.0f, 10.0f);

    test.setMat4("proj", glm::value_ptr(proj));
    test.setMat4("view", glm::value_ptr(view));
    float angle = SDL_GetTicks() / 1000.f;
    glm::vec3 fuck = glm::vec3(0.f, 0.f, 1.f);

    float transitiontime = 0.005f;
    followmouse = followmouse * (1 - timedelta *  transitiontime) + x * (timedelta * transitiontime);
    timedelta = (SDL_GetTicks() * 1.f) - lasttick;
    lasttick = SDL_GetTicks();
<<<<<<< HEAD
    glm::mat4 rotateMat = glm::rotate(x * 0.01f, fuck);

    glm::vec3 lightPos = glm::vec3(sin(SDL_GetTicks() / 1000.f), cos(SDL_GetTicks() / 1000.f), sin(SDL_GetTicks() / 1000.f) * cos(SDL_GetTicks() / 1000.f));
    glUniform3fv(glGetUniformLocation(test.shaderID(), "lightPos"), 1,  glm::value_ptr(lightPos));
=======
    glm::mat4 rotateMat = glm::rotate(x * 0.001f, fuck);
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b

    test.setMat4("rotate", glm::value_ptr(rotateMat));
    graphicsDevice.clear();
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, textureTest.id());
    GraphicEngine::instance()->draw(vao, &test, 36);
<<<<<<< HEAD

    for(int i = 0; i < 100; i++)
    {
      count += sin(i) * 0.01f;
      glm::mat4 translatem = glm::translate(rotateMat, glm::vec3(sin((SDL_GetTicks() / 1000.f) * count ), cos((SDL_GetTicks() / 1000.f) * count ), tan((SDL_GetTicks() / 1000.f) * count )));
      glm::mat4 scale = glm::scale(translatem, glm::vec3(0.5f, 0.5f, 0.5f));
      test.setMat4("rotate", glm::value_ptr(scale));
      GraphicEngine::instance()->draw(vao, &test, 36);
      //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
=======
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
>>>>>>> 8c0cb95fe648bb3c7abdb41dd0763fadbf44ce2b
    graphicsDevice.swap();
  }

  graphicsDevice.close();

  return 0;
}
