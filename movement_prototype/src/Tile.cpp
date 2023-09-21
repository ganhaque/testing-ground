// Tile.cpp

#include "Tile.h"
#include "raylib.h"
#include <iostream>

Tile::Tile(const std::string& id, int x, int y, bool interactable, bool blockMovement)
  : id(id),
  x(x),
  y(y),
  interactable(interactable),
  blockMovement(blockMovement)
{}

void Tile::interact() {
  if (interactable) {
    std::cout << "Interacting with tile " << id << std::endl;
  }
}

void Tile::draw(int gridSize) {
  // Draw the chest tile at the specified grid position
  DrawRectangle(x * gridSize, y * gridSize, gridSize, gridSize, RAYWHITE);
}
