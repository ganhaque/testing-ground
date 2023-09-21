// Game.h
#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Character.h"
#include "vector"
#include <memory>

enum GameState {
  START_MENU,
  IN_GAME
};


class Game {
  private:
    std::unique_ptr<Character> player; // Use a unique_ptr for deferred initialization
  public:
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    const int gameHeight = 800;
    const int gridSize = 50;
    // const int gridSize = 100;

    GameState gameState;

    std::string currentRoomId;
    std::vector<Tile> interactableTiles; // Vector to store interactable tiles
    std::vector<TransitionTile> transitionTiles;
    std::vector<std::string> completed; // Vector to store interactable tiles

    // Character player;

    int grid[16*2][8*2];
    // int grid[16][10];

    double lastMoveTime;
    double moveSpeed;

    Game();

    void loadRoom(std::string roomId);
    void extracted();
    void handleUserInput();
    bool isValidMove(int newX, int newY);
    void spawnTiles(); // Function to spawn tiles
    void run();
    // void initialize();
    void saveToJson(const std::string& filename);
    void loadSaveJson(const std::string& filename);
};
