#include <stdio.h>
#include "Texture.h"

Texture::Texture(std::string internalFormatName, std::string formatName,
                 int width, int height, const GLvoid* pixels,
                 bool linearFiltering, bool mirrorRepeat)
                 : _internalFormat(internalFormatName), _format(formatName)
{
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
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
}
