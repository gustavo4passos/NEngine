#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class GameObject
{
public:
  ~GameObject() {}
  virtual void update(unsigned int gameTime) = 0;
  virtual void draw() = 0;
};

#endif
