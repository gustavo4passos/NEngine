#include "util/SDLHandler.h"
#include "Shader.h"

SDL_Window* window;
SDL_GLContext context;

int main(int argc, char** args)
{
  SDLHandler::init("NEngine", 960, 544, window, &context);

  Shader test("shaders/vs.vs", "shaders/fs.fs");

  bool running = true;
  while(running)
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = false;
      }
      if(e.type == SDL_KEYUP)
      {
        if(e.key.keysym.sym == SDLK_ESCAPE)
        {
          running = false;
        }
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
