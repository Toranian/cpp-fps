#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"
#include "raylib.h"

class Player : public Entity {
public:
  Player(Vector3 position, Vector3 velocity, Vector3 force, BoundingBox bounds,
         float speed);

  void Update();
  void Draw();

  Vector3 position;
  Vector3 velocity;
  Vector3 force;

  BoundingBox bounds;

  float speed;
};

#endif
