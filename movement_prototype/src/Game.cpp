// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "StringParser.h"
#include "nlohmann/json.hpp"
#include <raylib.h>

Game::Game() : moveSpeed(0.2) {
  gameState = START_MENU; // Set the initial state to "start"
  printf("moveSpeed in constructor: %f\n", moveSpeed);

  // Initialize grid (adjust size accordingly)
  for (int x = 0; x < screenWidth / gridSize; x++) {
    for (int y = 0; y < screenHeight / gridSize; y++) {
      // grid[x][y] = (x == 2 && y == 3) ? 1 : 0; // Set an obstacle
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
  // spawnTiles();

  // loadSaveJson("savegame");

  // std::string input1 = "1-hp_pot";
  // int intValue;
  // std::string stringValue;
  //
  // StringParser::ParseString(input1, intValue, stringValue);
  //
  // std::cout << "Parsed: int=" << intValue << ", str=" << stringValue << std::endl;
  //
  // std::string input2 = "05-06";
  // int firstInt, secondInt;
  //
  // StringParser::ParseCoordinate(input2, firstInt, secondInt);
  // std::cout << "Parsed ID: int1=" << firstInt << ", int2=" << secondInt << std::endl;
}

void Game::loadSaveJson(const std::string& filename) {
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

      // Deserialize the JSON data into member variables
      // gameState = static_cast<GameState>(root.value("gameState", START_MENU));
      currentRoomId = root.value("currentRoomId", "");
      std::cout << "currentRoomId parsed from JSON is: " << currentRoomId << std::endl;

      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
      }

      // You can add more deserialization logic for other members here
      inputFile.close();
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
      // return false; // Loading failed
    }
  }
  else {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}

void Game::saveToJson(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Serialize member data to JSON
  // root["gameState"] = gameState;
  root["currentRoomId"] = currentRoomId;
  root["completed"] = nlohmann::json::array();

  for (const std::string& item : completed) {
    root["completed"].push_back(item);
  }

  // Create a JSON writer
  std::ofstream outputFile(fullFilePath);

  if (outputFile.is_open()) {
    // Write JSON to the output file
    outputFile << root.dump(4); // Pretty print with 4 spaces
    outputFile.close();
  }
  else {
    fprintf(stderr, "Unable to open the file for writing\n");
  }
}

void Game::loadRoom(std::string roomId) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;
      // Parse transition tiles
      for (const auto& transitionData : root["transitionTiles"]) {
        int tileX = transitionData["x"];
        int tileY = transitionData["y"];
        std::string destinationRoomId = transitionData["destinationRoomId"];
        TransitionTile transitionTile(tileX, tileY, destinationRoomId);
        transitionTiles.push_back(transitionTile);
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
}

void Game::handleUserInput() {
  double currentTime = GetTime();
  double deltaTimeSinceLastMove = currentTime - lastMoveTime;
  if (deltaTimeSinceLastMove < moveSpeed) {
    fprintf(stderr,"too soon\n");
    return; // Too soon for another move
  }
  else {
    // fprintf(stderr, "deltaTimeSinceLastMove: %f\n", deltaTimeSinceLastMove);
    fprintf(stderr, "moveSpeed: %f\n", moveSpeed);
    // fprintf(stderr, "Equality: %b\n", deltaTimeSinceLastMove < moveSpeed);
  }


  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    // case KEY_LEFT:
    //   player->move(player->x-1, player->y);
    //   player->facing = Direction::LEFT;
    //   break;
    // case KEY_DOWN:
    //   player->move(player->x, player->y+1);
    //   player->facing = Direction::DOWN;
    //   break;
    // case KEY_UP:
    //   player->move(player->x, player->y-1);
    //   player->facing = Direction::UP;
    //   break;
    // case KEY_RIGHT:
    //   player->move(player->x+1, player->y);
    // player->facing = Direction::RIGHT;
    //   break;
    case KEY_S:
      fprintf(stderr, "%s\n", "saved to savegame.json");
      saveToJson("savegame");
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      int targetX = player->x;
      int targetY = player->y;

      switch (player->facing) {
        case Direction::UP:
          targetY--;
          break;
        case Direction::DOWN:
          targetY++;
          break;
        case Direction::LEFT:
          targetX--;
          break;
        case Direction::RIGHT:
          targetX++;
          break;
      }
      // Check if the target position is within bounds and if there's an interactable tile at the target position
      for (Tile tile : interactableTiles) {
        if (tile.x == targetX && tile.y == targetY) {
          tile.interact(); // Call the interact method of the tile
          break; // Exit the loop once an interactable tile is found
        }
      }
      break;
  }


  // player->updateAnimation();

  int newX = player->x;
  int newY = player->y;

  if (IsKeyDown(KEY_RIGHT)) {
    player->facing = Direction::RIGHT;
    newX++;
  }
  else if (IsKeyDown(KEY_LEFT)) {
    player->facing = Direction::LEFT;
    newX--;
  }
  else if (IsKeyDown(KEY_DOWN)) {
    player->facing = Direction::DOWN;
    newY++;
  }
  else if (IsKeyDown(KEY_UP)) {
    player->facing = Direction::UP;
    newY--;
  }

  // no movement
  if (newX == player->x && newY == player->y) return;

  // Check if the new position is out of bounds
  if (
      newX < 0 ||
      newX >= (screenWidth / gridSize) ||
      newY < 0 ||
      newY >= (gameHeight / gridSize)
     ) {
    fprintf(stderr, "out of bound: %d, %d\n", newX, newY);
    // Check if there's a transition tile in the direction the player is moving
    // for (const TransitionTile& tile : transitionTiles) {
    //   if ((tile.x == newX && tile.y == newY) && tile.destinationRoomId != "") {
    //     // Load the destination room based on the transition tile's destinationRoomId
    //     loadRoom(tile.destinationRoomId);
    //     break;
    //   }
    // }
    return; // Player moved to a new room, no need to continue with the current input
  }
  else {
    player->move(newX, newY);
    lastMoveTime = currentTime;
    fprintf(stderr, "lastMoveTime is %f\n", lastMoveTime);
  }
}

bool Game::isValidMove(int newX, int newY) {
  return (newX >= 0 && newX < (screenWidth / gridSize) && newY >= 0 && newY < (screenHeight / gridSize) && grid[newX][newY] == 0);
}

void Game::spawnTiles() {
  // TODO:
  // Spawn your tiles here
  // ChestTile* chestTile = new ChestTile("chest_1", 3, 3);
  // interactableTiles.push_back(chestTile);
}

void Game::run() {
  InitWindow(screenWidth, screenHeight, "Grid-Based Movement with Interactive Objects");

  // Character playerCharacter(1, 1); // Create the character object
  player = std::make_unique<Character>(1, 1); // Create the character object

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (gameState == START_MENU) {
      BeginDrawing();
      DrawText("Press Space to Continue or something idk", screenWidth / 2 - 50, screenHeight / 2, 20, RAYWHITE);
      EndDrawing();
      if (IsKeyPressed(KEY_SPACE)) {
        gameState = IN_GAME;
      }
    }
    else if (gameState == IN_GAME) {
      handleUserInput();

      BeginDrawing();
      // ClearBackground(RAYWHITE);
      ClearBackground(DARKGRAY);

      // Draw the grid
      for (int x = 0; x < screenWidth; x += gridSize) {
        for (int y = 0; y < gameHeight; y += gridSize) {
          if (grid[x / gridSize][y / gridSize] == 1) {
            DrawRectangle(x, y, gridSize, gridSize, DARKGRAY);
          }
          else {
            // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
            DrawRectangleLines(x, y, gridSize, gridSize, BLACK);
          }
        }
      }

      // TODO: implement draw for tiles object
      for (Tile tile : interactableTiles) {
        tile.draw(gridSize);
      }

      // Draw the player character
      player->draw(gridSize);
      EndDrawing();
    }
  }

  // for (Tile tile : interactableTiles) {
  // delete tile;
  // }

  UnloadTexture(player->texture);

  CloseWindow();
}

