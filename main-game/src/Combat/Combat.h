// Exploration.h
#pragma once

#include <string.h>
#include <string>
#include "../GameState.h"
#include <queue>
// #include "../Room.h"

#include "../Game.h"

// class Game;

class Combat : public GameState {

  public:
    ~Combat() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void initialize() override;
    void exit() override;

    Room currentRoom;

    Texture2D background;
    // Texture2D overworldFg;

    std::vector<Unit> units;
    int currentUnitIndex;
    bool isRoundOver;
    int currentRound;
    void startRound();

    // Helpers

};
