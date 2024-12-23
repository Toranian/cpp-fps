#include "Bullet.h"
#include "raylib.h"
#include "raymath.h"
using namespace std;

Bullet::Bullet(Vector3 position, Vector3 velocity, Vector3 direction,
               BoundingBox bounds, float speed)
    : position(position), velocity(velocity), direction(direction),
      bounds(bounds), speed(speed) {}

void Bullet::Update() {
  velocity = Vector3Scale(direction, 0.05f);
  position = Vector3Add(position, velocity);
}

void Bullet::Draw() { DrawSphere(position, 0.3f, Color{0, 0, 255, 200}); }
