#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#define GLEW_STATIC
#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_Image.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Initializes SDL, Creates an OpenGL context, a window an stores a reference to both
// Also responsible for checking errors, a managing the window and context status
class GraphicsDevice
{
public:
  GraphicsDevice(const char* title, int windowWidth, int windowHeight, int glMajorVersion, int glMinorVersion, bool fullscreen = false, bool vsync = false, bool alphaEnabled = false);
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

  void setWindowSize(unsigned int windowWidth, unsigned int windowHeight);
  void toggleFullscreen();
  void toggleVsync();
  void showCursor(bool visible);

  // Returns information about the OpenGL context version and Graphic Card
  const char* graphicAdapterString();

private:
  // Stores the initialization status (true = successfully initialized, false otherwise)
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
