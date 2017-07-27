#include "Game.h"
#include "InputHandler.h"
#include "Shader.h"
#include "AudioEngine.h"
#include "Texture.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "GraphicEngine.h"
#include "Hero.h"
#include <SDL2/SDL.h>

#include <vector>
#include <string>

Game::Game(const char* windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int glMajorVersion, unsigned int glMinorVersion, bool fullscreen, bool vsync)
{
  _graphicsDevice = new GraphicsDevice(windowTitle, windowWidth, windowHeight, glMajorVersion, glMinorVersion, fullscreen, vsync);
  _graphicsDevice->clearColor(0.f, 0.f, 0.f, 1.f);

  _audioDevice = new AudioDevice();
}

Game::~Game()
{
  delete _graphicsDevice;
  _graphicsDevice = NULL;

  delete _audioDevice;
  _audioDevice = NULL;
}

void Game::handleInput()
{
  InputHandler::instance()->update();
  if(InputHandler::instance()->keyUp(SDL_SCANCODE_ESCAPE)) _running = false;
  if(InputHandler::instance()->keyUp(SDL_SCANCODE_F5)) _graphicsDevice->toggleFullscreen();
  if(InputHandler::instance()->closedWindow()) _running = false;
}

void Game::update()
{}

void Game::draw()
{
  _graphicsDevice->clearColor(.3f, .1f, .9f, 1.f);
  _graphicsDevice->clear();
  _graphicsDevice->swap();
}

void Game::run()
{
  Shader test("../shaders/vs.vs", "../shaders/fs.fs");

  // Hero myhero = Hero("../resources/sprites/megaman.png", 100, 100, &test);
  Hero myhero("../resources/sprites/megaman.png", 100, 100, &test);

  _graphicsDevice->checkForErrors();
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

  int source = AudioEngine::instance()->createSource();
  int northernWind = AudioEngine::instance()->loadWAV("../resources/audio/background/northern_wind.wav", true, 16);
  AudioEngine::instance()->play(source, northernWind);

  Texture textureTest = Texture("../resources/sprites/meteorite.png", "RGBA", "RGBA", true);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  test.use();
  test.vertexAttribPointer("position", 3, 11, 0);
  test.vertexAttribPointer("color", 3, 11, 5);
  test.vertexAttribPointer("texcoord", 2, 11, 6);
  test.vertexAttribPointer("normal", 3, 11, 8);

  int major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  printf("OpenGL version: %i.%i on %s\n", major, minor, renderer);

  _graphicsDevice->checkForErrors();

  float count = 1;

  // Starts the main loop
  _running = true;
  while(_running)
  {
    int x, y;
    SDL_GetMouseState(&x, &y);

    glm::mat4 view = glm::lookAt(
    glm::vec3(1.2f, 2.2f, 1.2f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
    );

    glEnable(GL_DEPTH_TEST);
    glm::mat4 proj = glm::perspective(glm::radians(45.f), float(_graphicsDevice->windowWidth()) / _graphicsDevice->windowHeight(), 1.0f, 10.0f);

    test.setMat4("proj", glm::value_ptr(proj));
    test.setMat4("view", glm::value_ptr(view));
    float angle = SDL_GetTicks() / 1000.f;
    glm::vec3 fuck = glm::vec3(0.f, 0.f, 1.f);

    glm::mat4 rotateMat = glm::rotate(glm::radians(SDL_GetTicks() * 0.05f), fuck);

    glm::vec3 lightPos = glm::vec3(sin(SDL_GetTicks() / 1000.f), cos(SDL_GetTicks() / 1000.f), sin(SDL_GetTicks() / 1000.f) * cos(SDL_GetTicks() / 1000.f));
    glUniform3fv(glGetUniformLocation(test.id(), "lightPos"), 1,  glm::value_ptr(lightPos));

    test.setMat4("rotate", glm::value_ptr(rotateMat));
    _graphicsDevice->clear();
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, textureTest.id());
    GraphicEngine::instance()->draw(vao, &test, 0, 36);

    for(int i = 0; i < 100; i++)
    {
      count += sin(i) * 0.01f;
      glm::mat4 translatem = glm::translate(rotateMat, glm::vec3(sin((SDL_GetTicks() / 1000.f) * count ), cos((SDL_GetTicks() / 1000.f) * count ), tan((SDL_GetTicks() / 1000.f) * count )));
      glm::mat4 scale = glm::scale(translatem, glm::vec3(0.5f, 0.5f, 0.5f));
      test.setMat4("rotate", glm::value_ptr(scale));
      GraphicEngine::instance()->draw(vao, &test, 0, 36);
      //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    _graphicsDevice->swap();

    handleInput();
    //update();
    //draw();
  }
}

void Game::close()
{
  _graphicsDevice->checkForErrors();
  _graphicsDevice->close();
}
