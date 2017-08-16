#include "PhysicsEngine.h"
#include "Player.h"
#include "World.h"
#include <stdio.h>

// Starts static instance as 0
PhysicsEngine* PhysicsEngine::_instance = 0;

PhysicsEngine::PhysicsEngine()
{
  // Start references as null. Call connectToTheWorld to anchor reference
  _world = NULL;
  _player = NULL;
}

void PhysicsEngine::connectToTheWorld(World* world, Player* player)
{
  _world = world;
  _player = player;
}

void PhysicsEngine::disconnect()
{
  _world = NULL;
  _player = NULL;
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
  if(_world == NULL && _player == NULL)
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

Vector2D PhysicsEngine::detectCollision(Box originalPosition, Box destination)
{
  Box furthestPosition = { originalPosition.id, originalPosition.x, originalPosition.y, originalPosition.right, originalPosition.bottom, originalPosition.width, originalPosition.height };

  Vector2D movementToTry = Vector2D(destination.x, destination.y) - Vector2D(originalPosition.x, originalPosition.y);
  int steps = int(movementToTry.length() * 2) + 1;
  Vector2D oneStep = movementToTry / steps;

  Box finalPosition = furthestPosition;
  for(int i = 1; i <= steps; i++)
  {
    finalPosition = furthestPosition;
    furthestPosition.x = originalPosition.x + (oneStep.x() * i);
    furthestPosition.y = originalPosition.y + (oneStep.y() * i);
    furthestPosition.right = originalPosition.right + (oneStep.x() * i);
    furthestPosition.bottom = originalPosition.bottom + (oneStep.y() * i);

    if(checkCollisionWithWorld(furthestPosition))
    {
      bool diagonalMove = (movementToTry.x() != 0 && movementToTry.y() != 0) ? true : false;
      if(diagonalMove)
      {
        int stepsLeft = steps - i - 1;

        Vector2D remainingHorizontalMovement(oneStep.x() * stepsLeft, 0);
        Box finalHorizontalMovement = finalPosition;
        finalHorizontalMovement.x += remainingHorizontalMovement.x();
        finalHorizontalMovement.right += remainingHorizontalMovement.x();
        Vector2D finalHorizontalMovementVector = detectCollision(finalPosition, finalHorizontalMovement);

        Vector2D remainingVerticalMovement(0, oneStep.y() * stepsLeft);
        Box finalVerticalMovement = finalPosition;
        finalVerticalMovement.y += remainingVerticalMovement.y();
        finalVerticalMovement.bottom += remainingVerticalMovement.y();
        Vector2D finalVerticalMovementVector = detectCollision(finalPosition, finalVerticalMovement);

        finalPosition.x = finalHorizontalMovementVector.x();
        finalPosition.right += finalPosition.x;
        finalPosition.y = finalVerticalMovementVector.y();
        finalPosition.bottom += finalPosition.y;
      }
      break;
    }
  }

  return Vector2D(finalPosition.x, finalPosition.y);
}
