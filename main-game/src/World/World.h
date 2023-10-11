// World.h
#pragma once

#include <string.h>
#include "../GameState.h"
#include "Room.h"
#include "Entity.h"
#include "Player.h"

#include "../Game.h"

// class Game;

class World : public GameState {
  public:
    World(std::string roomId); // destructor
    ~World() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    const double moveSpeed = 0.1;
    double lastMoveTime = 0;

    int grid[20][12];
    // int rows = sizeof(grid) / sizeof(grid[0]);
    // int columns = sizeof(grid[0]) / sizeof(grid[0][0]);
    int columns = sizeof(grid) / sizeof(grid[0]);
    int rows = sizeof(grid[0]) / sizeof(grid[0][0]);

    std::vector<Entity*> entities;
    Player* player = nullptr;

    // these will only be used when loadSave() & saveSave() is called
    //// player data
    int playerX = 0;
    int playerY = 0;
    std::string playerFacing = "down";

    // Input


    std::queue<std::pair<int, int>> pathQueue;

    Room currentRoom;

    Texture2D background;

    void loadRoom(const std::string& roomId);

    // Helpers
    std::string inputHelper(std::string facing);
    void findShortestPath(Game& game, int startX, int startY, int targetX, int targetY);

  private:
    void resetGrid(); // set all in grid to 0
    void sortGameObjects();
    void clearPathQueue();
    // void handleKeyPressO();

    // processMovement();
};
