// Game.h
#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Character.h"
#include "vector"
#include <memory>

class Game {
  private:
    std::unique_ptr<Character> player; // Use a unique_ptr for deferred initialization
  public:
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    const int gridSize = 50;
    std::vector<Tile*> interactableTiles; // Vector to store interactable tiles

    // Character player;

    int grid[16*2][10*2];

    double lastMoveTime;
    double moveSpeed = 0.1;

    Game();

    void HandleUserInput();
    bool isValidMove(int newX, int newY);
    void spawnTiles(); // Function to spawn tiles
    void run();
    void Initialize();
};
