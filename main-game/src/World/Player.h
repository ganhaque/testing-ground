#pragma once
#include "Entity.h"
// #include "enums.h"
#include <string>

// TODO: a lot lol
class Player : public Entity {
  public:
    std::string facing;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing
        );

    void move(int newX, int newY);


    // Combat specific
    int health;
    int damage;
    int initiative;
    bool hasTakenTurn = false;

    // Shared
    void render(int gridWidth, int gridHeight);
};


