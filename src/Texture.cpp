#include <stdio.h>
#include "Texture.h"

Texture::Texture(std::string path, std::string internalFormatName, std::string formatName, bool linearFiltering, bool mirrorRepeat)
                 : _internalFormat(internalFormatName), _format(formatName)
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

    if(internalFormatName == "RGB") internalFormat = GL_RGB;
    else if(internalFormatName == "RGBA") internalFormat = GL_RGBA;
    else
    {
      printf("Texture format not recognized: %s. Setting it as standard GL_RGB.\n", internalFormatName.c_str());
      internalFormat = GL_RGB;
    }

    if(formatName == "RGB") format = GL_RGB;
    else if(formatName == "RGBA") format = GL_RGBA;
    else
    {
      printf("Texture format not recognized: %s. Setting it as standard GL_RGB.\n", formatName.c_str());
      format = GL_RGB;
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
