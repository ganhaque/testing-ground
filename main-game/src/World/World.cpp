#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"

World::World(
    std::string roomId
    ) {
  resetGrid();

  // TODO: error
  // loadRoom(roomId);

  std::string roomFilePath = "./assets/room/" + roomId + "-bg.png";
  if (std::ifstream(roomFilePath)) {
    background = LoadTexture(roomFilePath.c_str());
  }
  else {
    fprintf(stderr, "not found bg image file %s\n", roomFilePath.c_str());
  }

  player = new Player(
      "player-01",
      playerX,
      playerY,
      playerFacing
      );
  entities.push_back(player);
}

World::~World() {
  return;
}

void World::render(Game& game) {
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  // DrawTexture(overworldBg, 0, 0, WHITE);

  Rectangle srcRect = {
    0,
    0,
    static_cast<float>(background.width),
    static_cast<float>(background.height)
  };
  Rectangle destRect = {
    0,
    0,
    static_cast<float>(game.settings.screenWidth),
    static_cast<float>((game.settings.screenHeight - game.settings.overworldUIHeight))
  };
  // DrawTexture(overworldBg, 0, 0, WHITE);
  DrawTexturePro(
      background,
      srcRect,
      destRect,
      { 0, 0 },
      0.0f,
      WHITE
      );

  // Draw the grid (debug only)
  for (int x = 0; x < columns; x++) {
    for (int y = 0; y < rows; y++) {
      if (grid[x][y] == 1) {
        DrawRectangle(
            x * game.settings.gridWidth,
            y * game.settings.gridHeight,
            game.settings.gridWidth,
            game.settings.gridHeight,
            DARKGRAY
            );
      }
      else {
        // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
        DrawRectangleLines(
            x * game.settings.gridWidth,
            y * game.settings.gridHeight,
            game.settings.gridWidth,
            game.settings.gridHeight,
            BLACK
            );
      }
    }
  }

  for (Entity* entity : entities) {
    // Call the render method for each object through the pointer
    entity->render(game.settings.gridWidth, game.settings.gridHeight);
  }

  // TODO: draw currentRoomId-fg.png here

  Vector2 mousePosition = GetMousePosition();
  int gridX = mousePosition.x / game.settings.gridWidth;
  int gridY = mousePosition.y / game.settings.gridHeight;
  for (int x = 0; x < columns; x++) {
    for (int y = 0; y < rows; y++) {
      // Check if mouse is over this grid tile
      if (x == gridX && y == gridY) {
        // DrawRectangle(x, y, settings.gridWidth, settings.gridHeight, ColorAlpha(WHITE, 30));
        Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
        DrawRectangle(
            x * game.settings.gridWidth,
            y * game.settings.gridHeight,
            game.settings.gridWidth,
            game.settings.gridHeight,
            highlightColor
            );
      }
    }
  }
  game.renderDialog();
  EndDrawing();
}

void World::loadRoom(const std::string& roomId) {
  const std::string saveFilePath = "./json/room/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;

      // TODO: rename this
      std::string roomFilePath = "./assets/room/" + roomId;
      background = LoadTexture((roomFilePath + "-bg.png").c_str());

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


void World::update(Game& game) {}
