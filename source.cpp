#include "src/GraphicsDevice.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/InputHandler.h"
#include "src/GraphicEngine.h"
#include "src/Shader.h"
#include "src/Texture.h"

int main(int argc, char** args)
{
  GraphicsDevice graphicsDevice("NEngine", 1366, 768, false, true);

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
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
  };

  GLuint elements[] =
  {
    1, 2, 3
  };

  SDL_Surface* surf = SDL_LoadBMP("../resources/sprites/img.bmp");
  printf("Texture x and w %i and %i\n", surf->w, surf->h);
  Texture textureTest = Texture("RGB", "RGB", surf->w, surf->h, surf->pixels);

  SDL_FreeSurface(surf);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  test.use();

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "position"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "position"));

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "color"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "color"));

  glVertexAttribPointer(glGetAttribLocation(test.shaderID(), "texcoord"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
  glEnableVertexAttribArray(glGetAttribLocation(test.shaderID(), "texcoord"));

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
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1366 / 768.f, 1.0f, 10.0f);

    test.setMat4("proj", glm::value_ptr(proj));
    test.setMat4("view", glm::value_ptr(view));
    float angle = SDL_GetTicks() / 1000.f;
    glm::vec3 fuck = glm::vec3(0.f, 0.f, 1.f);

    float transitiontime = 0.005f;
    followmouse = followmouse * (1 - timedelta *  transitiontime) + x * (timedelta * transitiontime);
    timedelta = (SDL_GetTicks() * 1.f) - lasttick;
    lasttick = SDL_GetTicks();
    glm::mat4 rotateMat = glm::rotate(x * 0.001f, fuck);

    test.setMat4("rotate", glm::value_ptr(rotateMat));
    graphicsDevice.clear();
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, textureTest.id());
    GraphicEngine::instance()->draw(vao, &test, 36);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    graphicsDevice.swap();
  }

  graphicsDevice.close();

  return 0;
}
