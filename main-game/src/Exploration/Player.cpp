// Player.cpp
#include "Player.h"
#include "../Helper.h"

Player::Player(
    const std::string& playerId,
    int playerX,
    int playerY,
    std::string facing
    ) :
  facing(facing)
{
  id = playerId;
  x = playerX;
  y = playerY;
  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

void Player::render(int gridWidth, int gridHeight) {
  // TODO:
  // DrawTextureRec(
  //     texture,
  //     frameRects[static_cast<int>(facing)],
  //     {
  //     static_cast<float>(x) * gridSize,
  //     static_cast<float>(y) * gridSize
  //     },
  //     WHITE);
  // PLACEHOLDER:
  DrawRectangle(
      x * gridWidth,
      y * gridHeight,
      gridWidth,
      gridHeight,
      RED);
  return;
}

void Player::move(int newX, int newY) {
  x = newX;
  y = newY;
}
