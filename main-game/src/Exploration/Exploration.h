// Exploration.h
#pragma once

#include <string.h>
#include "../GameState.h"
#include "Room.h"

#include "../Game.h"

// class Game;

class Exploration : public GameState {
  public:
    Exploration(std::string roomId); // destructor
    ~Exploration() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void initialize() override;
    void exit() override;

    const double moveSpeed = 0.1;
    double lastMoveTime = 0;

    std::queue<std::pair<int, int>> pathQueue;

    Room currentRoom;

    Texture2D background;

    void loadRoom(const std::string& roomId);

    // Helpers
    std::string inputHelper(std::string facing);
    void findShortestPath(Game& game, int startX, int startY, int targetX, int targetY);
};
