#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>

// Constructor: Initialize the player's position, width, and height
// Make sure to define these in the header file
Player::Player(Vector3 position, Vector3 velocity, Vector3 force,
               BoundingBox bounds, float speed)
    : position(position), velocity(velocity), force(force), bounds(bounds),
      speed(speed) {}

void Player::Update() {

  velocity = {0, 0, 0};

  if (IsKeyDown(KEY_W)) {
    velocity.x = speed;
  }
  if (IsKeyDown(KEY_S)) {
    velocity.x = -speed;
  }
  if (IsKeyDown(KEY_A)) {
    velocity.y = -speed;
  }
  if (IsKeyDown(KEY_D)) {
    velocity.y = speed;
  }

  position += velocity;
}

void Player::Draw() {}
