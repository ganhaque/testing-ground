// Tile.cpp
#include "Tile.h"
#include "../Helper.h"

Tile::Tile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
    ) :
  isBlockMovement(isBlockMovement)
{
  id = tileId;
  x = tileX;
  y = tileY;
  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

void Tile::render(int gridWidth, int gridHeight) {
  // TODO: 
  return;
}
