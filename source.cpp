#include <cmath>
#include "src/GraphicsDevice.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/AudioEngine.h"
#include "src/InputHandler.h"
#include "src/GraphicEngine.h"
#include "src/Shader.h"
#include "src/Texture.h"
#include "src/AudioDevice.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;

int main(int argc, char** args)
{
  srand(time(NULL));

  AudioDevice audioDevice = AudioDevice();
  if(audioDevice.initializationStatus())
  {
    AudioEngine::instance();
  }
  GraphicsDevice graphicsDevice("NEngine", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 2, false, true);
  if(graphicsDevice.initializationStatus())
    {
      graphicsDevice.clearColor(0.1f, 0.1f, 0.1f, 1.f);
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

      int source = AudioEngine::instance()->createSource();
      printf("Source: %i\n", source);
      int northernWind = AudioEngine::instance()->loadWAV("../resources/audio/background/northern_wind.wav", true, 16);
      AudioEngine::instance()->play(source, northernWind);

      SDL_Surface* surf = IMG_Load("../resources/sprites/meteorite.png");
      if(surf == NULL){ printf("SDL_IMage error: %s\n", IMG_GetError());}
      Texture textureTest = Texture("RGBA", "RGBA", surf->w, surf->h, surf->pixels, true);

      SDL_FreeSurface(surf);

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
      printf("OpenGL version: %i.%i\n", major, minor);

      graphicsDevice.checkForErrors();

      float count = 1;

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
        glm::mat4 proj = glm::perspective(glm::radians(45.f), float(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 10.0f);

        test.setMat4("proj", glm::value_ptr(proj));
        test.setMat4("view", glm::value_ptr(view));
        float angle = SDL_GetTicks() / 1000.f;
        glm::vec3 fuck = glm::vec3(0.f, 0.f, 1.f);

        glm::mat4 rotateMat = glm::rotate(glm::radians(SDL_GetTicks() * 0.05f), fuck);

        glm::vec3 lightPos = glm::vec3(sin(SDL_GetTicks() / 1000.f), cos(SDL_GetTicks() / 1000.f), sin(SDL_GetTicks() / 1000.f) * cos(SDL_GetTicks() / 1000.f));
        glUniform3fv(glGetUniformLocation(test.id(), "lightPos"), 1,  glm::value_ptr(lightPos));

        test.setMat4("rotate", glm::value_ptr(rotateMat));
        graphicsDevice.clear();
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
        graphicsDevice.swap();
      }

      AudioEngine::instance()->clean();
      graphicsDevice.checkForErrors();
      graphicsDevice.close();
    }
  return 0;
}
