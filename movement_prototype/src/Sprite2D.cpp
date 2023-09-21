#include "Sprite2D.h"

Sprite2D::Sprite2D(const char* imagePath) {
  // Load the sprite sheet texture
  texture = LoadTexture(imagePath);

  // Set up source rectangles for each animation frame
  frameRects[0] = { 0, 0, 50.0f, 50.0f };
  frameRects[1] = { 0, 50.0f, 50.0f, 50.0f };
  frameRects[2] = { 0, 100.0f, 50.0f, 50.0f };
  frameRects[3] = { 0, 150.0f, 50.0f, 50.0f };
}

void Sprite2D::draw(int x, int y, int gridSize) {
  DrawTextureRec(
      texture,
      frameRects[currentFrame],
      {
      static_cast<float>(x) * gridSize,
      static_cast<float>(y) * gridSize
      },
      WHITE);
}

// void Sprite2D::updateAnimation() {
//     if (IsKeyDown(KEY_RIGHT)) {
//         currentFrame = 3; // Right-facing frame
//     }
//     else if (IsKeyDown(KEY_LEFT)) {
//         currentFrame = 0; // Left-facing frame
//     }
//     else if (IsKeyDown(KEY_DOWN)) {
//         currentFrame = 1; // Down-facing frame
//     }
//     else if (IsKeyDown(KEY_UP)) {
//         currentFrame = 2; // Up-facing frame
//     }
// }
//
