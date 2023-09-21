// Tile.h
#pragma once
// #ifndef TILE_H
// #define TILE_H

#include <string>
#include "raylib.h"
#include "Character.h"

class Tile {
  public:
    std::string id;
    bool interactable;
    bool blockMovement;
    int x; // Add x coordinate
    int y; // Add y coordinate

    Tile(const std::string& id, int x, int y, bool interactable = false, bool blockMovement = false);

    virtual void interact();
    void draw(int gridSize);
};

class TransitionTile {
  public:
    int x, y;
    std::string destinationRoomId;

    TransitionTile(
      int x,
      int y,
      const std::string& destinationRoomId
    ) : x(x), y(y), destinationRoomId(destinationRoomId) {}

    // You can add more methods and properties if needed
};
