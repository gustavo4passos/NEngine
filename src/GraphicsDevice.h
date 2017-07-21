#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class GraphicsDevice
{
public:
  GraphicsDevice(const char* title, int windowWidth, int windowHeight, bool fullscreen = false, bool vsync = false);
  SDL_Window* window() { return _window; }
  void clear();
  void swap();

  // Getters
  unsigned int windowWidth()  const { return _windowWidth; }
  unsigned int windowHeight() const { return _windowHeight; }

  void toggleFullscreen();

private:
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
