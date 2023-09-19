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

ChestTile::ChestTile(const std::string& id, int x, int y)
  : Tile(id, x, y, true, true) {}

NpcTile::NpcTile(const std::string& id, int x, int y)
  : Tile(id, x, y, true, true) {}

BattleTile::BattleTile(const std::string& id, int x, int y)
  : Tile(id, x, y, true, true) {}

TerrainTile::TerrainTile(const std::string& id, int x, int y)
  : Tile(id, x, y, false, true) {}

TransitionTile::TransitionTile(const std::string& id, const std::string& destinationRoomId, int x, int y)
  : Tile(id, x, y, false, false),
  destinationRoomId(destinationRoomId)
{}

void ChestTile::open() {
  std::cout << "Opening chest tile " << id << std::endl;
  // Additional logic specific to ChestTile
}

void NpcTile::talk() {
  std::cout << "Talking to NPC tile " << id << std::endl;
  // Additional logic specific to NpcTile
}

void BattleTile::startBattle() {
  std::cout << "Starting battle on tile " << id << std::endl;
  // Additional logic specific to BattleTile
}

void TransitionTile::enter() {
  std::cout << "Entering transition tile " << id << " to room " << destinationRoomId << std::endl;
  // Additional logic specific to TransitionTile
}

void ChestTile::draw(int gridSize) {
  // Draw the chest tile at the specified grid position
  DrawRectangle(x * gridSize, y * gridSize, gridSize, gridSize, BLUE);
}

