// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <raylib.h>
#include "nlohmann/json.hpp"
#include "MainMenu.h"

Game::Game() {
  // Initialize grid (adjust size accordingly)
  initialize();
  resetGrid();
}


void Game::run() {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "Game Title");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (currentState != nullptr) {
      currentState->processInput(*this);
      currentState->update(*this);
      currentState->render(*this);
    }
  }

  // TODO: unload stuffs when game about to close to prevent memory leak
  // UnloadTexture(player->texture);

  CloseWindow();
}


void Game::initialize() {
  // MainMenu* mainMenuState = new MainMenu();
  // changeState(mainMenuState);
  // changeState("mainMenu");
  MainMenu* newState = new MainMenu();
  currentState = newState;


  player = new Player(
      "player-01",
      playerX,
      playerY,
      playerFacing
      );
  entities.push_back(player);
}

// void Game::changeState(GameState* newState) {
// }

void Game::changeState(std::string state) {
  // if (currentState != nullptr) {
  //   currentState->exit();
  //   delete currentState; // This will call the destructor of the derived class.
  //   currentState = nullptr; // Set to nullptr to avoid using a dangling pointer.
  // }
  if (state == "mainMenu") {
    MainMenu* newState = new MainMenu();
    currentState->exit();
    delete currentState;
    currentState = newState;
    currentState->initialize();
  }
  else if (state == "exploration") {
    loadSave("savedata-01");
    Exploration* newState = new Exploration();
    currentState->exit();
    delete currentState;
    currentState = newState;
    currentState->initialize();

  }
  else if (state == "combat") {
    Combat* newState = new Combat();
    currentState->exit();
    delete currentState;
    currentState = newState;
    currentState->initialize();
  }
}

void Game::renderDialog() {
  bool isHover = (GetMousePosition().y / gridHeight) >= 12;
  if (!dialogQueue.empty()) {
    // Draw a dialogue box
    DrawRectangle(
        0,
        screenHeight - overworldUIHeight,
        screenWidth,
        overworldUIHeight,
        DARKGRAY
        );
    if (isHover) {
      Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
      DrawRectangle(
          0,
          screenHeight - overworldUIHeight,
          screenWidth,
          overworldUIHeight,
          highlightColor
          );
    }
    else {
    }
    // Draw the current dialog text
    DrawText(
        dialogQueue.front().c_str(),
        10,  // X position of the text
        screenHeight - overworldUIHeight + 10,  // Y position of the text
        20,  // Font size
        WHITE
        );
  }
}

void Game::loadSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Read the JSON data from the file
  std::ifstream inputFile(fullFilePath);

  if (inputFile.is_open()) {
    // Parse the JSON data
    try {
      inputFile >> root;
      // TODO: this part is WIP, more work need to be done here
      // Deserialize the JSON data into member variables
      currentRoomId = root.value("currentRoomId", "");
      loadRoom(currentRoomId);
      // const std::string roomFilePath = "./assets/room/";
      std::string roomFilePath = "./assets/room/" + currentRoomId;
      // overworldBg = LoadTexture((roomFilePath + "-bg.png").c_str());
      // TODO: also load overworldFg

      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
      }

      // playerX = root.value("playerX", 0);
      // playerY = root.value("playerY", 0);
      // playerFacing = root.value("playerFacing", "down");
      //
      // player = new Player(
      //     "player-01",
      //     playerX,
      //     playerY,
      //     playerFacing
      //     );
      // entities.push_back(player);

      // TODO: Add inventory parsing logic here
      // TODO: Add more deserialization logic for other members here

      inputFile.close();
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
    }
  }
  else {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}
//
void Game::loadRoom(const std::string& roomId) {
  const std::string saveFilePath = "./json/room/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;
      // TODO: this part is also WIP, more work need to be done here
      // TODO: when parsing room Tile,
      // if Tile.isBlockMovement == true then set grid[tileX][tileY] = 1

      // Parse transition tiles
      for (const auto& transitionData : root["transitionTiles"]) {
        int tileX = transitionData["x"];
        int tileY = transitionData["y"];
        int enterX = transitionData["enterX"];
        int enterY = transitionData["enterY"];
        std::string destinationRoomId = transitionData["destinationRoomId"];
        // TODO: create new TransitionTile & push into the transitionTiles vector
        // TransitionTile transitionTile(tileX, tileY, destinationRoomId);
        // transitionTiles.push_back(transitionTile);
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
}

void Game::saveSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;
  // TODO: this part is also WIP, more work need to be done here
  // Mostly,
  // - Player x, y, and other data members also need to be saved
  // - Room does not need to be saved since we load it when we load the save

  // Serialize member data to JSON
  root["currentRoomId"] = currentRoomId;
  root["completed"] = nlohmann::json::array();

  for (const std::string& item : completed) {
    root["completed"].push_back(item);
  }

  // Create a JSON writer
  std::ofstream outputFile(fullFilePath);

  if (outputFile.is_open()) {
    // Write JSON to the output file
    outputFile << root.dump(2); // Pretty print with 2 spaces
    outputFile.close();
  }
  else {
    fprintf(stderr, "Unable to open the file for writing\n");
  }
}

void Game::loadTile(const std::string& tileId) {
  std::string tileType = Helper::parseGameObjectType(tileId);
  if (tileType == "chest") {
    const std::string chestFilePath = "./json/chest/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = chestFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
        // TODO: parse chest json data here
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else if (tileType == "combat") {
    // TODO: load combat encounter, blah blah blah
    const std::string combatFilePath = "./json/combat/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = combatFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
        // TODO: parse combat json data here
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  // TODO: add more parsing for other tile type here
  else if (true) {
  }
}



void Game::resetGrid() {
  for (int x = 0; x < screenWidth / gridWidth; x++) {
    for (int y = 0; y < (screenHeight - overworldUIHeight) / gridHeight; y++) {
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
}
