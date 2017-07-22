#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"

class Player : public GameObject
{
public:
  void update();
  void draw();
};

#endif
