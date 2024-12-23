#include "./entities/player/Player.h"
#include "entities/bullet/Bullet.h"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1600;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera first person");

  // Define the camera to look into our 3d world (position, target, up vector)
  Camera camera = {0};
  camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
  Vector3 initSpawn = camera.position;
  camera.target = (Vector3){0.0f, 2.0f, 0.0f}; // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  int cameraMode = CAMERA_FIRST_PERSON;
  Player player(camera.position, (Vector3){0.0f, 0.0f, 0.0f},
                (Vector3){0.0f, 0.0f, 0.0f}, (BoundingBox){0}, 0.1f);

  std::vector<Bullet> entities;

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  //
  Vector3 movement = {0.0f, 0.0f, 0.0f};
  float rotation = 0.0f;

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    player.Update();
    Vector3 movement = player.velocity;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      movement = movement * 2.5f;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

      Vector3 forward = Vector3Normalize(
          Vector3Subtract(camera.target, camera.position)); // Get the

      // Spawn a bullet!
      Bullet bullet(camera.position, {0, 0, 0}, forward, (BoundingBox){0},
                    0.1f);
      entities.push_back(bullet);

    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
      cameraMode = CAMERA_FIRST_PERSON;
      DisableCursor();
    }

    UpdateCameraPro(&camera, movement,
                    (Vector3){
                        GetMouseDelta().x * 0.75f, // Rotation: yaw
                        GetMouseDelta().y * 0.75f, // Rotation: pitch
                        rotation,
                    },
                    GetMouseWheelMove() * 2.0f);

    BeginDrawing();

    ClearBackground(Color{31, 31, 31, 255});

    BeginMode3D(camera);

    // DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
    //           LIGHTGRAY); // Draw ground
    // DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
    //          BLUE); // Draw a blue wall
    // DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
    //          LIME); // Draw a green wall
    // DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
    //          GOLD); // Draw a yellow wall

    // Update & draw the entities
    for (int i = 0; i < entities.size(); i++) {
      entities[i].Update();
      entities[i].Draw();
    }

    // Draw floor grid
    for (int i = -200; i < 200; i++) {

      float distanceFactor =
          (float)abs(i) / 100.0f; // Normalize distance (0 to 1)
      unsigned char opacity =
          (int)((1.0f - distanceFactor) *
                255); // Invert factor for closer = more opaque

      DrawLine3D((Vector3){(float)i, 0.01f, -200.0f},
                 (Vector3){(float)i, 0.01f, 200.0f},
                 Color{60, 60, 60, opacity});

      DrawLine3D((Vector3){-200.0f, 0.01f, (float)i},
                 (Vector3){200.0f, 0.01f, (float)i},
                 Color{60, 60, 60, opacity});
    }

    // Draw player cube
    DrawCube(camera.target, 0.5f, 0.5f, 0.5f, Color{0, 0, 0, 0});
    EndMode3D();

    // Draw crosshairs
    DrawLine(screenWidth / 2.0f - 20, screenHeight / 2.0f,
             screenWidth / 2.0f + 20, screenHeight / 2.0f,
             Color{255, 255, 255, 200});
    DrawLine(screenWidth / 2.0f, screenHeight / 2.0f - 20, screenWidth / 2.0f,
             screenHeight / 2.0f + 20, Color{255, 255, 255, 200});

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
