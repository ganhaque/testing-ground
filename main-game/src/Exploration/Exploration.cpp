#include "Exploration.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"

void Exploration::processInput(Game& game) {
  double currentTime = GetTime();
  double deltaTimeSinceLastMove = currentTime - lastMoveTime;

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePosition = GetMousePosition();
    int targetX = mousePosition.x / game.gridWidth;
    int targetY = mousePosition.y / game.gridHeight;

    fprintf(stderr, "mousePosition: %d, %d\n", targetX, targetY);

    // If player hit the UI/Dialog area
    if (targetY >= 12) {
      if (!game.dialogQueue.empty()) {
        game.dialogQueue.pop();
        return;
      }
      // NOTE: UI button interaction should go here
    }

    std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue
    findShortestPath(game, game.player->x, game.player->y, targetX, targetY);
    if (!pathQueue.empty()) {
      // reset move timer for smoother transition?
      deltaTimeSinceLastMove = 0;
    }
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_O:
      {
        fprintf(stderr, "%s\n", "o was pressed");
        std::string placeholderDialog = "Lorem ipsum...";
        int d4Result = GetRandomValue(1, 4);
        switch (d4Result) {
          case 1:
            game.dialogQueue.push("That's a lotta Damage!!!!!");
            break;
          case 2:
            game.dialogQueue.push("Hi, this is dialog.");
            break;
          case 3:
            game.dialogQueue.push("Almost!");
            break;
          case 4:
            game.dialogQueue.push(placeholderDialog);
            break;
        }
        break;
      }
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      // TODO: This is place holder
      // plan is to have a button/UI to select different save
      // like savedata-02 -> savedata-08
      fprintf(stderr, "%s\n", "saved to savedata-01.json");
      game.saveSave("savedata-01");
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      if (!game.dialogQueue.empty()) {
        game.dialogQueue.pop();
        break;
      }
      int targetX = game.player->x;
      int targetY = game.player->y;

      if (game.player->facing == "up") {
        targetY--;
      }
      else if (game.player->facing == "down") {
        targetY++;
      }
      else if (game.player->facing == "left") {
        targetX--;
      }
      else if (game.player->facing == "right") {
        targetX++;
      }
      else {
        fprintf(stderr, "invalid player->facing direction");
        return;
      }

      for (Entity* entity : game.entities) {
        bool isInterableObject =
          Helper::parseGameObjectType(entity->id) != "player" &&
          entity->x == targetX &&
          entity->y == targetY
          ;
        if (isInterableObject) {
          game.loadTile(entity->id);
        }
      }
      break;
  }

  int newX = game.player->x;
  int newY = game.player->y;
  std::string direction = inputHelper(game.player->facing);

  if (direction == "none") {
    // Continue moving along the path until the queue is empty
    while (!pathQueue.empty()) {
      if (deltaTimeSinceLastMove < moveSpeed) {
        break; // Too soon for another move
      }
      std::pair<int, int> nextPos = pathQueue.front();
      pathQueue.pop();
      game.player->move(nextPos.first, nextPos.second);
      lastMoveTime = currentTime;
      break;
    }
    return;
  }
  else if (direction == "right") {
    game.player->facing = "right";
    newX++;
  }
  else if (direction == "left") {
    game.player->facing = "left";
    newX--;
  }
  else if (direction == "down") {
    game.player->facing = "down";
    newY++;
  }
  else if (direction == "up") {
    game.player->facing = "up";
    newY--;
  }
  else {
    fprintf(stderr, "error direction\n");
  }

  std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue

  if (deltaTimeSinceLastMove < moveSpeed) {
    return; // Too soon for another move
  }

  // NOTE: this might be uneccessary, add back if break
  // no movement
  // if (newX == player->x && newY == player->y) {
  // }

  // Check if the new position is out of bounds
  bool isOutOfBound = newX < 0 ||
    newX >= (game.screenWidth / game.gridWidth) ||
    newY < 0 ||
    newY >= ((game.screenHeight - game.overworldUIHeight) / game.gridHeight);
  if (isOutOfBound) {
    fprintf(stderr, "out of bound: %d, %d\n", newX, newY);
    // TODO: if current tile is transition tile
    if (true) {
      // TODO: move player to transitionTile.enterX and enterY
      // player->move(0, 0);
      return;
    }
    return; // Player moved to a new room, no need to continue with the current input
  }
  else if (game.grid[newX][newY] == 1) {
    // no movement, terrain or tile block
    return;
  }
  else {
    game.player->move(newX, newY);
    lastMoveTime = currentTime;
  }
}

std::string Exploration::inputHelper(std::string facing) {
  std::string lastDirection = facing;

  if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) return "right";
  if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) return "left";
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) return "up";
  if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) return "down";

  bool isNoMovementKeyHeld = !(
      IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ||
      IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ||
      IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ||
      IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)
      );

  if (isNoMovementKeyHeld) {
    return "none";
  }

  bool isNoChange =
    (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && lastDirection == "right" ||
    (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && lastDirection == "left" ||
    (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && lastDirection == "down" ||
    (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && lastDirection == "up";

  if (isNoChange) {
    return lastDirection;
  }
  else {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
      return "right";
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
      return "left";
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
      return "down";
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
      return "up";
    }
  }

  return "error";
}


/*
TODO: This can be optimized further by keeping track of the target
the player is walking to then decide if the current path is "good"
if good -> calculate from old target to new target instead
if bad -> same as before
*/
void Exploration::findShortestPath(Game& game, int startX, int startY, int targetX, int targetY) {
  std::pair<int, int> start = { startX, startY};
  std::pair<int, int> target = { targetX, targetY};
  int dx[] = {1, -1, 0, 0};  // Possible movements in x-direction
  int dy[] = {0, 0, 1, -1};  // Possible movements in y-direction
  std::vector<std::vector<std::pair<int, int>>> parent(20, std::vector<std::pair<int, int>>(12, {-1, -1}));
  std::queue<std::pair<int, int>> q;
  q.push(start);

  if (game.grid[targetX][targetY] != 0) {
    fprintf(stderr, "Not reachable!\n");
    return;
  }

  while (!q.empty()) {
    std::pair<int, int> curr = q.front();
    q.pop();

    if (curr == target) {
      // Reconstruct the path from target to start
      std::vector<std::pair<int, int>> path;
      while (curr.first != start.first || curr.second != start.second) {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
      }
      path.push_back(start);

      // update the pathQueue
      for (int i = path.size() - 1; i >= 0; --i) {
        pathQueue.push(path[i]);
      }
      return;
    }

    for (int i = 0; i < 4; ++i) {
      int newX = curr.first + dx[i];
      int newY = curr.second + dy[i];
      bool isValid =
        newX >= 0 &&
        newX < 20 &&
        newY >= 0 &&
        newY < 12 &&
        game.grid[newX][newY] == 0;

      if (isValid && parent[newX][newY].first == -1) {
        q.push({newX, newY});
        parent[newX][newY] = curr;
      }
    }
  }

  fprintf(stderr, "No path found!\n");
}


void Exploration::render(Game& game) {
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  // DrawTexture(overworldBg, 0, 0, WHITE);

  Rectangle srcRect = { 0, 0, static_cast<float>(background.width), static_cast<float>(background.height) };
  Rectangle destRect = { 0, 0, static_cast<float>(game.screenWidth), static_cast<float>((game.screenHeight - game.overworldUIHeight)) };
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
  for (int x = 0; x < game.screenWidth; x += game.gridWidth) {
    for (int y = 0; y < (game.screenHeight - game.overworldUIHeight); y += game.gridHeight) {
      if (game.grid[x / game.gridWidth][y / game.gridHeight] == 1) {
        DrawRectangle(x, y, game.gridWidth, game.gridHeight, DARKGRAY);
      }
      else {
        // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
        DrawRectangleLines(x, y, game.gridWidth, game.gridHeight, BLACK);
      }
    }
  }

  for (Entity* entity : game.entities) {
    // Call the render method for each object through the pointer
    entity->render(game.gridWidth, game.gridHeight);
  }

  // TODO: draw currentRoomId-fg.png here

  Vector2 mousePosition = GetMousePosition();
  int gridX = mousePosition.x / game.gridWidth;
  int gridY = mousePosition.y / game.gridHeight;
  for (int x = 0; x < game.screenWidth; x += game.gridWidth) {
    for (int y = 0; y < (game.screenHeight - game.overworldUIHeight); y += game.gridHeight) {
      // Check if mouse is over this grid tile
      if (x / game.gridWidth == gridX && y / game.gridHeight == gridY) {
        // DrawRectangle(x, y, gridWidth, gridHeight, ColorAlpha(WHITE, 30));
        Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
        DrawRectangle(x, y, game.gridWidth, game.gridHeight, highlightColor);
      }
    }
  }
  game.renderDialog();
  EndDrawing();
}

void Exploration::loadRoom(const std::string& roomId) {
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


void Exploration::update(Game& game) {}
void Exploration::initialize() {}
void Exploration::exit() {}

Exploration::Exploration(
    std::string roomId
    ) {
  loadRoom(roomId);
}

Exploration::~Exploration() {
  return;
}
