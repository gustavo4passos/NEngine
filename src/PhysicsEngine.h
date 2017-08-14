#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>

struct Box;
class Player;
class World;
class Vector2D;

class PhysicsEngine
{
public:
  static PhysicsEngine* instance()
  {
    if(_instance == 0)
    {
      _instance = new PhysicsEngine();
    }

    return _instance;
  }

  // Add reference to player and world
  void connectToTheWorld(World* world, Player* player);
  // Remove referencres
  void disconnect();

  // Checks for collision between player and world
  bool checkCollision(Box a, Box b);
  bool checkCollisionWithWorld(Box player);
  Vector2D detectCollision(Box originalPosition, Box destination);

private:
  PhysicsEngine();
  static PhysicsEngine* _instance;

  // Reference to the player and the world for physics calculation
  Player* _player;
  World* _world;


};

#endif
