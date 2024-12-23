

/*******************************************************************************************
 *
 *   raylib [core] example - 3d camera first person
 *
 *   Example originally created with raylib 1.3, last time updated with
 *raylib 1.3
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 *OSI-certified, BSD-like license that allows static linking with closed source
 *software
 *
 *   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "./entities/player/Player.h"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include <cmath>
#include <iostream>
using namespace std;

#define MAX_COLUMNS 20

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
  camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  int cameraMode = CAMERA_FIRST_PERSON;

  // Generates some random columns
  float heights[MAX_COLUMNS] = {0};
  Vector3 positions[MAX_COLUMNS] = {0};
  Color colors[MAX_COLUMNS] = {0};

  for (int i = 0; i < MAX_COLUMNS; i++) {
    heights[i] = (float)GetRandomValue(1, 12);
    positions[i] = (Vector3){(float)GetRandomValue(-15, 15), heights[i] / 2.0f,
                             (float)GetRandomValue(-15, 15)};
    colors[i] =
        (Color){GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255};
  }

  Player player(camera.position, (Vector3){0.0f, 0.0f, 0.0f},
                (Vector3){0.0f, 0.0f, 0.0f}, (BoundingBox){0}, 0.1f);

  // DisableCursor(); // Limit cursor to relative movement inside the window

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
      cameraMode = CAMERA_FIRST_PERSON;
      DisableCursor();
    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
      cameraMode = CAMERA_ORBITAL;
      EnableCursor();
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

    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
              LIGHTGRAY); // Draw ground
    DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
             BLUE); // Draw a blue wall
    DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
             LIME); // Draw a green wall
    DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
             GOLD); // Draw a yellow wall

    // Draw floor grid
    for (int i = -20; i < 20; i++) {
      DrawLine3D((Vector3){(float)i, 0.01f, -20.0f},
                 (Vector3){(float)i, 0.01f, 20.0f}, DARKGRAY);

      DrawLine3D((Vector3){-20.0f, 0.01f, (float)i},
                 (Vector3){20.0f, 0.01f, (float)i}, DARKGRAY);
    }

    DrawSphere((Vector3){5.0f, 1.0f, 1.0f}, 1.0f, GOLD);

    // Draw some cubes around
    // for (int i = 0; i < MAX_COLUMNS; i++) {
    //   DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
    //   DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
    // }

    // Draw player cube
    DrawCube(camera.target, 0.5f, 0.5f, 0.5f, Color{0, 0, 0, 0});
    // DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);

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
