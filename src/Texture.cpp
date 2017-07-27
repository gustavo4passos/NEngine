#include <stdio.h>
#include "Texture.h"

Texture::Texture(std::string path, bool linearFiltering, bool mirrorRepeat)
{
  SDL_Surface* surface = IMG_Load(path.c_str());
  // Check if surface loaded correctly
  if(surface == NULL)
  {
    printf("TEXTURE ERROR: Unable to load texture. Error: %s\n", IMG_GetError());
    // Set id as -1, which is an invalid value to a OpenGL object
    _id = -1;
    // Set dimensions to 0
    _width = _height = 0;
  }
  else
  {
    _width = surface->w;
    _height = surface->h;

    GLint internalFormat;
    GLenum format;

    // Check the internal format of the texutre, and chose the GLenum accordginly
    if(surface->format->format == SDL_PIXELFORMAT_RGB24)
    {
      internalFormat = format = GL_RGB;
    }
    else if(surface->format->format == SDL_PIXELFORMAT_RGBA32)
    {
      internalFormat = format = GL_RGBA;
    }
    else
    {
      printf("Texture format not recognized: %s. Setting it as standard GL_RGB.\n");
      internalFormat = GL_RGB;
    }

    glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);

    // Set linear filtering
    if(linearFiltering)
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    // Or use nearest neighbor filtering
    else
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // Set image repeat, if the tex coordinates are outside the texture
    if(mirrorRepeat)
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    }
    // If image is not set to repeat, clamp edges
    else
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    // Load pixels on video memory
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    // Free ram
    SDL_FreeSurface(surface);

    //Unbind texture from context after loading
    glBindTexture(GL_TEXTURE_2D, 0);

    //Check for errors
    GLenum error = glGetError();
    while(error != GL_NO_ERROR)
    {
      printf("OPENGL ERROR: Error while sending texture to video memory. %s Error: %s\n", path.c_str(), gluErrorString(error));
      error = glGetError();
    }

  }
}

void Texture::use()
{
  // Binds texture to thea active OpenGL context
  glBindTexture(GL_TEXTURE_2D, _id);
}
