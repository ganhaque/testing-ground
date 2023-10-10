// Tile.h
#pragma once

#include <string>
#include "raylib.h"
#include "Entity.h"

class Tile : public Entity {
  public:
    // NOTE: id, x, and y are inherited from GameObject already
    bool isBlockMovement;

    Tile(
        const std::string& tileId,
        int tileX,
        int tileY,
        bool isBlockMovement = false
        );

    // virtual void interact();
    // void draw(int gridSize);
    void render(int gridWidth, int gridHeight);
};
