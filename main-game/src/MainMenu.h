#pragma once
#include "GameState.h"
#include "Game.h"

class MainMenu : public GameState {
  public:
    ~MainMenu() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void initialize() override;
    void exit() override;
};

