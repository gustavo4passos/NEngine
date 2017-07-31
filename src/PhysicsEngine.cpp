#include "PhysicsEngine.h"
#include "Hero.h"
#include "World.h"
#include <stdio.h>

// Starts static instance as 0
PhysicsEngine* PhysicsEngine::_instance = 0;

PhysicsEngine::PhysicsEngine()
{
  // Start references as null. Call connectToTheWorld to anchor reference
  _world = NULL;
  _hero = NULL;
}

void PhysicsEngine::connectToTheWorld(World* world, Hero* hero)
{
  _world = world;
  _hero = hero;
}

void PhysicsEngine::disconnect()
{
  _world = NULL;
  _hero = NULL;
}

bool PhysicsEngine::checkCollision(Box a, Box b)
{
  if(a.x < b.right  &&
     a.right > b.x  &&
     a.y < b.bottom &&
     a.bottom > b.y)
     {
       return true;
     }
     return false;
}

bool PhysicsEngine::checkCollisionWithWorld(Box player)
{
  // Check if the engine is connected to a world
  if(_world == NULL && _hero == NULL)
  {
    printf("PHYSICS ENGINE ERROR: Unable to check collision with the world. Not connected to any world.\n (Need to call connecToTheWorld?)\n");
    return false;
  }
  // If connected, check for collisiob
  for(int i = 0; i < _world->_collisionLayer.size(); i++)
  {
    if(checkCollision(player, _world->_collisionLayer[i])) return true;
  }
  // No collision was detected
  return false;
}
