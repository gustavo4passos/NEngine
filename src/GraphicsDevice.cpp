  #include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice(const char* title, int windowWidth, int windowHeight, int glMajorVersion, int glMinorVersion, bool fullscreen, bool vsync, bool alphaEnabled)
 : _windowWidth(windowWidth), _windowHeight(windowHeight), _isFullscreen(fullscreen), _vsync(vsync)
{
  //Check if SDL was initialized correctly (SDL_Init returns a negative value in case it was not able to initialize SDL)
  if( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    printf("SDL ERROR: Unable to initialize SDL. Error: %s\n", SDL_GetError());
  }
  else
  {
    #ifdef LOG
    printf("SDL successfully initialized.\n");
    #endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion);

    //Fullscreen flag
    Uint32 flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL : SDL_WINDOW_OPENGL;
    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, flags);

    if(_window == NULL)
    {
      printf("SDL ERROR: Unable to create window. Error:%s\n", SDL_GetError());
      _initializationStatus = false;
    }
    else
    {
      _glContext = SDL_GL_CreateContext(_window);

      if(_glContext == NULL)
      {
        printf("SDL ERROR: Unable to create OpenGL context from SDL. Error: %s\n", SDL_GetError());
        _initializationStatus = false;
      }
      else
      {
        printf("OpenGL context successfully created.\n");

        glewExperimental = GL_TRUE;
        GLenum glewErr = glewInit();

        if(glewErr != GLEW_NO_ERROR)
        {
          printf("SDL ERROR: Unable to initialize Glew. Error: %s\n", glewGetErrorString(glewErr));
          _initializationStatus = false;
        }
        else
        {
          printf("Glew successfully initialized.\n");

          glClearColor(0.f, 0.f, 0.0f, 1.f);

          // Initialize SDL Image (PNG loader, and other formats that we won't need
          // We wan't to initialize only the PNG loader
          int flags = IMG_INIT_PNG | IMG_INIT_JPG;
          int succesffullyInitialized = IMG_Init(flags);
          if((flags & succesffullyInitialized) != flags)
          {
            printf("SDL IMAGE ERROR: Unable to initialize SDL_Image correctly. Error: %s\n", IMG_GetError());
            _initializationStatus = false;
          }
          else
          {
            printf("SDL_Image successfully initialized.\n");
            _initializationStatus = true;

            if(vsync)
            {
              if(SDL_GL_SetSwapInterval(1) < 0)
              {
                printf("SDL ERROR: Unable to enable Vsync. Error: %s\n", SDL_GetError());
              }
            }

            if(alphaEnabled)
            {
              printf("Transparency enabled.\n");
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            // Query information about the context
            GLint majorVersion, minorVersion;
            glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
            glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
            // Query information about the video card
            const GLubyte* adapter = glGetString(GL_RENDERER);
            // Print data about the current context and graphic adapter
            printf("Graphic Adapter: %s\n", adapter);
            printf("OpenGL version %i.%i\n", majorVersion, minorVersion);
          }
        }
      }
    }
  }
}

void GraphicsDevice::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  glClearColor(red, green, blue, alpha);
}

void GraphicsDevice::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::swap()
{
  SDL_GL_SwapWindow(_window);
}

int GraphicsDevice::checkForErrors()
{
  // 0 = no errors found. -1 otherwise.
  int wereErrorsFound = 0;
  // Poll one event from the error queue
  GLenum error = glGetError();

  while(error != GL_NO_ERROR)
  {
    wereErrorsFound = -1;
    printf("OPENGL ERROR: %s\n", gluErrorString(error));
    // Checks if there are still errors in the queue
    error = glGetError();
  }

  return wereErrorsFound;
}

void GraphicsDevice::setWindowSize(unsigned int windowWidth, unsigned int windowHeight)
{
  SDL_SetWindowSize(_window, windowWidth, windowHeight);
}

void GraphicsDevice::toggleFullscreen()
{
  if(!_isFullscreen)
  {
    _isFullscreen = true;
    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(false);
  }
  else
  {
    _isFullscreen = false;
    SDL_SetWindowFullscreen(_window, 0);
    SDL_ShowCursor(true);
  }
}

void GraphicsDevice::toggleVsync()
{
  if(_vsync)
  {
    if(SDL_GL_SetSwapInterval(0) < 0)
    {
      printf("SDL ERROR: Unable to disable vsync. Error: %s\n", SDL_GetError());
    }
    else
    {
        _vsync = false;
    }
  }
  else
  {
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
      printf("SDL ERROR: Unable to enable vsync. Error: %s\n", SDL_GetError());
    }
    else
    {
      _vsync = true;
    }
  }
}

void GraphicsDevice::showCursor(bool visible)
{
  SDL_ShowCursor((visible) ? SDL_ENABLE : SDL_DISABLE);
}

void GraphicsDevice::close()
{
  SDL_DestroyWindow(_window);
  IMG_Quit();
  SDL_Quit();
}
