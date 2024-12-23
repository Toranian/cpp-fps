#ifndef BULLET_H
#define BULLET_H

#include "../Entity.h"
#include "raylib.h"

class Bullet : public Entity {
public:
  Bullet(Vector3 position, Vector3 velocity, Vector3 direction,
         BoundingBox bounds, float speed);

  void Update();
  void Draw();

  Vector3 position;
  Vector3 velocity;
  Vector3 direction;

  BoundingBox bounds;

  float speed = 0.1f;
};

#endif
