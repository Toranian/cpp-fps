#include "Bullet.h"
#include "raylib.h"
#include "raymath.h"
using namespace std;

Bullet::Bullet(Vector2 position, Vector2 direction, float speed)
    : position(position), direction(direction), speed(speed), width(5),
      height(5) {}

void Bullet::Update() {
  Vector2 velocity = {0, 0};
  velocity = Vector2Scale(direction, speed);
  position = Vector2Add(position, velocity);
}

void Bullet::Draw() {
  DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                width, height, BLUE);
}
