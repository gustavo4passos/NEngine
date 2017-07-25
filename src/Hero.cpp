#include "Hero.h"

Hero::Hero(const char* textureFilePath, int width, int height, Shader* shader,  float framesw, float framesh) : _width(width), _height(height)
{
  texture = new Texture(textureFilePath, "RGBA", "RGB");

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  GLfloat vertices[] =
  {  // Quad vertices         |  TexCoordinates
     0.f        , 0.f         , 0.f                                            , 0.f,
     width * 1.f, 0.f         , ((texture->width() / framesw) / texture->width()), 0.f,
     width * 1.f, height * 1.f, (texture->width() / framesw) / texture->width(), (texture->height() / framesh) / texture->height(),
    0.f        , height * 1.f, 0.f                                            , (texture->height() / framesh) / texture->height()
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  shader->vertexAttribPointer("position", 2, 4, 0.f);
  shader->vertexAttribPointer("texcoord", 2, 4, 2);
}

void Hero::update(unsigned int gameTime)
{
}

void Hero::draw()
{
}
