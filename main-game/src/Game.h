// Game.h
#pragma once
// #include "GameStates.h"

#include "Combat/Unit.h"
#include "raylib.h"
#include "vector"
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

#include "World/World.h"
#include "World/Entity.h"
#include "World/Player.h"
#include "World/Tile.h"

#include "Combat/Combat.h"
#include "MainMenu/MainMenu.h"

class GameState;

class GameSettings {
  public:
    int screenWidth = 1920 / 2;
    int screenHeight = 1080 / 2;
    int gridWidth = 96 / 2;
    int gridHeight = 80 / 2;
    int overworldUIHeight = 120 / 2;
};

class Game {
  public:
    Game();
    ~Game();

    void run();

    // resolution
    GameSettings settings;
    // TODO: add some way to change the resolution variables back and forth

    // DialogQueue dialogueQueue;
    std::queue<std::string> dialogQueue;

    // savedata.json contains
    std::string currentRoomId = "05-06";
    std::vector<std::string> completed;
    // std::vector<std::string> tempCompleted;

    // inventory mini-class (don't make a class for this yet)
    int gold = 0;
    std::vector<std::string> items;


    // Exploration* exploration;
    // MainMenu* mainMenu;

    GameState* world;

    GameState* currentState;
    // void processInput();
    // void update();
    // void render();

    void changeState(std::string state);

    void renderDialog();

    // NOTE: save to autosave.json whenever combat-> overworld or move to new room
    void loadSave(const std::string& filename);
    // void loadRoom(const std::string& roomId);
    void saveSave(const std::string& filename);
    // trigger when interact with a tile
    void loadTile(const std::string& tileId);

    // Helpers
};

