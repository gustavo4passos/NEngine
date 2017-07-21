#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class GameObject
{
public:
  virtual void update() = 0;
  virtual void draw() = 0;
};

#endif
