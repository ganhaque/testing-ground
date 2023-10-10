// Game.h
#pragma once
// #include "GameStates.h"

#include "Combat/Unit.h"
#include "raylib.h"
#include "vector"
#include "Exploration/Entity.h"
#include "Exploration/Player.h"
#include "Exploration/Tile.h"
#include "Helper.h"
#include <algorithm>
#include <memory>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <random>
#include <string_view>
#include <string>
// #include "enums.h"
#include "../external-libs/nlohmann/json.hpp"

#include "GameState.h"
#include "Exploration/Exploration.h"
#include "Combat/Combat.h"
#include "MainMenu/MainMenu.h"

class GameState;

class Game {
  public:
    Game();

    void run();

    // resolution
    const int screenWidth = 1920 / 2;
    const int screenHeight = 1080 / 2;
    const int gridWidth = 96 / 2;
    const int gridHeight = 80 / 2;
    const int overworldUIHeight = 120 / 2;
    // TODO: add some way to change the resolution variables back and forth

    int grid[20][12];
    // GameState gameState = GameState::start_menu;


    std::vector<Entity*> entities;
    Player* player = nullptr;

    // DialogQueue dialogueQueue;
    std::queue<std::string> dialogQueue;

    // savedata.json contains
    std::string currentRoomId = "05-06";
    std::vector<std::string> completed;
    // std::vector<std::string> tempCompleted;

    // inventory mini-class (don't make a class for this yet)
    int gold = 0;
    std::vector<std::string> items;

    // these will only be used when loadSave() & saveSave() is called
    //// player data
    int playerX = 0;
    int playerY = 0;
    std::string playerFacing = "down";

    // Exploration* exploration;
    // MainMenu* mainMenu;

    GameState* currentState;
    void initialize();
    void processInput();
    void update();
    void render();

    // void changeState(GameState* newState);
    void changeState(std::string state);

    void renderDialog();

    // NOTE: save to autosave.json whenever combat-> overworld or move to new room
    void loadSave(const std::string& filename);
    // void loadRoom(const std::string& roomId);
    void saveSave(const std::string& filename);
    // trigger when interact with a tile
    void loadTile(const std::string& tileId);

    // Helpers
    void resetGrid(); // set all in grid to 0
    void sortGameObjects();
};

