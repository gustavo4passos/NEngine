#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice(const char* title, int windowWidth, int windowHeight, bool fullscreen, bool vsync)
 : _windowWidth(windowWidth), _windowHeight(windowHeight), _isFullscreen(fullscreen), _vsync(vsync)
{
  //Check if SDL was initialized correctly (SDL_Init returns a negative value in case it was not able to initialize SDL)
  if( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    printf("SDL ERROR: Unable to initialize SDL. Error: %s\n", SDL_GetError());
  }
  else
  {
    printf("SDL successfully initialized.\n");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Fullscreen flag
    Uint32 flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL : SDL_WINDOW_OPENGL;
    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, flags);

    if(_window == NULL)
    {
      printf("SDL ERROR: Unable to create window. Error:%s\n", SDL_GetError());
    }
    else
    {
      _glContext = SDL_GL_CreateContext(_window);

      if(_glContext == NULL)
      {
        printf("SDL ERROR: Unable to create OpenGL context from SDL. Error: %s", SDL_GetError());
      }
      else
      {
        glewExperimental = GL_TRUE;
        GLenum glewErr = glewInit();

        if(glewErr != GLEW_NO_ERROR)
        {
          printf("SDL ERROR: Unable to initialize Glew. Error: %s\n", glewGetErrorString(glewErr));
        }
        else
        {
          glClearColor(0.f, 0.f, 0.0f, 1.f);

          if(vsync)
          {
            if(SDL_GL_SetSwapInterval(1) < 0)
            {
              printf("SDL ERROR: Unable to enable Vsync. Error: %s\n", SDL_GetError());
            }
          }

        }
      }
    }
  }
}

void GraphicsDevice::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::swap()
{
  SDL_GL_SwapWindow(_window);
}

void GraphicsDevice::toggleFullscreen()
{
  if(!_isFullscreen)
  {
    _isFullscreen = true;
    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
  }
  else
  {
    _isFullscreen = false;
    SDL_SetWindowFullscreen(_window, 0);
  }
}
