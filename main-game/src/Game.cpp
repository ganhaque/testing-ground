// Game.cpp
#include "Game.h"
#include <cstdio>

Game::Game() {
  InitWindow(settings.screenWidth, settings.screenHeight, "Project: Fox");
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  SetTargetFPS(60);

  // IMPORTANT: Any texture loading have to go after InitWindow

  // settings.settings.screenWidth = 1920 / 2;
  // settings.settings.screenHeight = 1080 / 2;
  world = new World(currentRoomId);

  // set initinal game state
  GameState* newState = new MainMenu();
  // GameState* newState = world;
  // GameState* newState = new Combat();
  currentState = newState;
}

Game::~Game() {
  delete currentState;
  delete world;

  CloseWindow();
}


void Game::run() {
  while (!WindowShouldClose()) {
    if (currentState != nullptr) {
      currentState->processInput(*this);
      currentState->update(*this);
      currentState->render(*this);
    }
  }
}

// TODO: FIX THIS!!!!!!
// NOTE: This is very very bad code (it work tho lol), pls fix !!!
void Game::changeState(std::string state) {
  GameState* newState = nullptr;

  if (state == "mainMenu") {
    fprintf(stderr, "gameState is now MainMenu!\n");
    newState = new MainMenu();
  }
  else if (state == "world") {
    if (currentState == world) {
      fprintf(stderr, "gameState is already world!!!\n");
      return;
    }
    else {
      fprintf(stderr, "gameState is now world!\n");
      // loadSave("savedata-01");
      delete currentState;
      currentState = world;
      return;
      // newState = new World(currentRoomId);

    }
  }
  else if (state == "combat") {
    fprintf(stderr, "gameState is now Combat!\n");
    newState = new Combat();
  }

  if (currentState != newState) {
    if (currentState != world) {
      delete currentState;
    }
    currentState = newState;
  }
}

void Game::renderDialog() {
  bool isHover = (GetMousePosition().y / settings.gridHeight) >= 12;
  if (!dialogQueue.empty()) {
    // Draw a dialogue box
    DrawRectangle(
        0,
        settings.screenHeight - settings.overworldUIHeight,
        settings.screenWidth,
        settings.overworldUIHeight,
        DARKGRAY
        );
    if (isHover) {
      Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
      DrawRectangle(
          0,
          settings.screenHeight - settings.overworldUIHeight,
          settings.screenWidth,
          settings.overworldUIHeight,
          highlightColor
          );
    }
    else {
    }
    // Draw the current dialog text
    DrawText(
        dialogQueue.front().c_str(),
        10,  // X position of the text
        settings.screenHeight - settings.overworldUIHeight + 10,  // Y position of the text
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
      // loadRoom(currentRoomId);
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
