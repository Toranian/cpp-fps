#ifndef BULLET_H
#define BULLET_H

#include "../Entity.h"
#include "raylib.h"

class Bullet : public Entity {
public:
  Bullet(Vector2 position, Vector2 direction, float speed);
  void Update();
  void Draw();

  Vector2 position;
  Vector2 direction;
  float speed;
  int width;
  int height;
};

#endif
