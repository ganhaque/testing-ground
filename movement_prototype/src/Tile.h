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

class ChestTile : public Tile {
public:
    ChestTile(const std::string& id, int x, int y);

    void open();
    void draw(int gridSize);
    void interact(char playerDirection);
};

class NpcTile : public Tile {
public:
    NpcTile(const std::string& id, int x, int y);

    void talk();
};

class BattleTile : public Tile {
public:
    BattleTile(const std::string& id, int x, int y);

    void startBattle();
};

class TerrainTile : public Tile {
public:
    TerrainTile(const std::string& id, int x, int y);
};

class TransitionTile : public Tile {
private:
    std::string destinationRoomId;

public:
    TransitionTile(const std::string& id, const std::string& destinationRoomId, int x, int y);

    void enter();
};

// #endif // TILE_H

