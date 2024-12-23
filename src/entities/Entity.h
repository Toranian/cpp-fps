
#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity {
public:
  virtual void Update() = 0;
  virtual void Draw() = 0;

  Vector3 position;
  Vector3 velocity;
  Vector3 force;

  BoundingBox bounds;
};

#endif
