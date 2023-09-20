// Character.cpp

#include "Character.h"
#include <cstdio>

// Character::Character(int startX, int startY) : x(startX), y(startY), facing(Direction::DOWN) {}

Character::Character(int startX, int startY) : x(startX), y(startY), facing(Direction::DOWN), currentFrame(0) {
  // Load the sprite sheet texture (adjust the path accordingly)
  texture = LoadTexture("./assets/Sample.png");

  // Set up source rectangles for each animation frame
  // for (int i = 0; i < 4; i++) {
  //   frameRects[i] = { 0, i * 50.0f, 50.0f, 50.0f };
  //   // frameRects[i] = { i * 50.0f, 0, 50.0f, 50.0f };
  // }
  frameRects[static_cast<int>(Direction::LEFT)] = { 0, 0, 50.0f, 50.0f };
  frameRects[static_cast<int>(Direction::DOWN)] = { 0, 50.0f, 50.0f, 50.0f };
  frameRects[static_cast<int>(Direction::UP)] = { 0, 100.0f, 50.0f, 50.0f };
  frameRects[static_cast<int>(Direction::RIGHT)] = { 0, 150.0f, 50.0f, 50.0f };

  // frameRects[static_cast<int>(Direction::LEFT)] = { 0, 0, 2*50.0f, 2*50.0f };
  // frameRects[static_cast<int>(Direction::DOWN)] = { 0, 2*50.0f, 2*50.0f, 2*50.0f };
  // frameRects[static_cast<int>(Direction::UP)] = { 0, 2*100.0f, 2*50.0f, 2*50.0f };
  // frameRects[static_cast<int>(Direction::RIGHT)] = { 0, 2*150.0f, 2*50.0f, 2*50.0f };
}

void Character::move(int newX, int newY) {
  x = newX;
  y = newY;
}

void Character::updateAnimation() {
  if (IsKeyDown(KEY_RIGHT)) {
    facing = Direction::RIGHT;
  }
  else if (IsKeyDown(KEY_LEFT)) {
    facing = Direction::LEFT;
  }
  else if (IsKeyDown(KEY_DOWN)) {
    facing = Direction::DOWN;
  }
  else if (IsKeyDown(KEY_UP)) {
    facing = Direction::UP;
  }

  // Cycle through the frames only if any movement key is pressed
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP)) {
    currentFrame = (currentFrame + 1) % 4;
  }
}
