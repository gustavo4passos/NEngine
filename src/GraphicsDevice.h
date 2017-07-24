#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#define GLEW_STATIC
#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_Image.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class GraphicsDevice
{
public:
  GraphicsDevice(const char* title, int windowWidth, int windowHeight, int glMajorVersion, int glMinorVersion, bool fullscreen = false, bool vsync = false);
  SDL_Window* window() { return _window; }

  //Changes the clear color
  void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  // Clears the screen
  void clear();
  // Swap buffers
  void swap();
  // Close and clean
  void close();
  // Check for OpenGL errors. Returns -1 if errors were found
  int checkForErrors();

  // Returns the initialization status. If something isn't initialized successfully, this will be false. Otherwise, it'll be true.
  bool initializationStatus() const { return _initializationStatus; }

  // Getters
  unsigned int windowWidth()  const { return _windowWidth; }
  unsigned int windowHeight() const { return _windowHeight; }

  void toggleFullscreen();
  void toggleVsync();

private:
    //Stores the initialization status
    bool _initializationStatus;

  // Window and OpenGL context
  SDL_Window* _window;
  SDL_GLContext _glContext;

  // Window attributes
  unsigned int _windowWidth;
  unsigned int _windowHeight;
  bool _isFullscreen;
  bool _vsync;

};

#endif
