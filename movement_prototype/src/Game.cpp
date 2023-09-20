// Game.cpp
#include "Game.h"
#include <iostream>
#include <fstream>
#include "StringParser.h"
#include <json/json.h>
#include <raylib.h>

Game::Game() {
  gameState = START_MENU; // Set the initial state to "start"

  // Initialize grid (adjust size accordingly)
  for (int x = 0; x < screenWidth / gridSize; x++) {
    for (int y = 0; y < screenHeight / gridSize; y++) {
      // grid[x][y] = (x == 2 && y == 3) ? 1 : 0; // Set an obstacle
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
  // spawnTiles();

  // Create a JSON parser
  Json::Value save;
  Json::CharReaderBuilder builder;
  std::string errs;

  // Read the save JSON data
  std::ifstream jsonFile("./json/save.json");

  if (parseFromStream(builder, jsonFile, &save, &errs)) {
    // JSON parsing succeeded
    std::cout << "Parsing succeeded." << std::endl;
    currentRoomId = save["currentRoomId"].asString();
    loadRoom(currentRoomId);

    currentRoomId = save["playerX"].asInt();

    // TODO: load completed
  }



  std::string input1 = "1-hp_pot";
  int intValue;
  std::string stringValue;

  StringParser::ParseString(input1, intValue, stringValue);

  std::cout << "Parsed: int=" << intValue << ", str=" << stringValue << std::endl;

  std::string input2 = "05-06";
  int firstInt, secondInt;

  StringParser::ParseCoordinate(input2, firstInt, secondInt);

  std::cout << "Parsed ID: int1=" << firstInt << ", int2=" << secondInt << std::endl;
}

void Game::loadRoom(std::string roomId) {
  // Create a JSON parser
  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string errs;

  // Read the JSON data from a file
  std::ifstream jsonFile("00-00.json");
  if (parseFromStream(builder, jsonFile, &root, &errs)) {

  }
}

void Game::HandleUserInput() {
  if (IsKeyPressed(KEY_SPACE)) {
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
    if (targetX >= 0 && targetX < (screenWidth / gridSize) && targetY >= 0 && targetY < (screenHeight / gridSize)) {
      for (Tile* tile : interactableTiles) {
        if (tile->x == targetX && tile->y == targetY) {
          tile->interact(); // Call the interact method of the tile
          break; // Exit the loop once an interactable tile is found
        }
      }
    }
  }

  const double currentTime = GetTime();
  const double deltaTime = currentTime - lastMoveTime;

  if (deltaTime < moveSpeed) {
    return; // Too soon for another move
  }

  // player->updateAnimation();

  int newX = player->x;
  int newY = player->y;

  if (IsKeyDown(KEY_RIGHT)) {
    player->facing = Direction::RIGHT;
    newX++;
    player->currentFrame = (player->currentFrame + 1) % 4; // Cycle through the frames
  }
  else if (IsKeyDown(KEY_LEFT)) {
    player->facing = Direction::LEFT;
    newX--;
    player->currentFrame = (player->currentFrame + 1) % 4; // Cycle through the frames
  }
  else if (IsKeyDown(KEY_DOWN)) {
    player->facing = Direction::DOWN;
    newY++;
    player->currentFrame = (player->currentFrame + 1) % 4; // Cycle through the frames
  }
  else if (IsKeyDown(KEY_UP)) {
    player->facing = Direction::UP;
    newY--;
    player->currentFrame = (player->currentFrame + 1) % 4; // Cycle through the frames
  }
  // printf("Current Frame: X=%f, Y=%f\n",
  //     player->frameRects[static_cast<int>(player->facing)].x,
  //     player->frameRects[static_cast<int>(player->facing)].y
  //     );

  if (isValidMove(newX, newY)) {
    player->move(newX, newY);
    // printf("New player coordinate: %d, %d\n", newX, newY);
    lastMoveTime = currentTime;
  }
}

bool Game::isValidMove(int newX, int newY) {
  return (newX >= 0 && newX < (screenWidth / gridSize) && newY >= 0 && newY < (screenHeight / gridSize) && grid[newX][newY] == 0);
}

void Game::spawnTiles() {
  // Spawn your tiles here
  ChestTile* chestTile = new ChestTile("chest_1", 3, 3);
  interactableTiles.push_back(chestTile);
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
      HandleUserInput();

      BeginDrawing();
      // ClearBackground(RAYWHITE);
      ClearBackground(DARKGRAY);

      // Draw the grid
      for (int x = 0; x < screenWidth; x += gridSize) {
        for (int y = 0; y < screenHeight; y += gridSize) {
          // if (grid[x / gridSize][y / gridSize] == 1) {
          // DrawRectangle(x, y, gridSize, gridSize, DARKGRAY);
          // }
          // else {
          DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
          // }
        }
      }

      // TODO: draw tiles/objects here
      for (Tile* tile : interactableTiles) {
        tile->draw(gridSize);
      }

      // Draw the player character
      // DrawRectangle(player->x * gridSize, player->y * gridSize, gridSize, gridSize, RED);
      // DrawTextureRec(player->texture, player->frameRects[static_cast<int>(player->facing)], { player->x * gridSize, player->y * gridSize }, WHITE);
      DrawTextureRec(player->texture, player->frameRects[static_cast<int>(player->facing)], { static_cast<float>(player->x) * gridSize, static_cast<float>(player->y) * gridSize }, WHITE);

      EndDrawing();
    }
  }

  for (Tile* tile : interactableTiles) {
    delete tile;
  }

  UnloadTexture(player->texture);

  CloseWindow();
}
