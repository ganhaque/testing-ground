#include "World.h"

void World::processInput(Game& game) {
  double currentTime = GetTime();
  double deltaTimeSinceLastMove = currentTime - lastMoveTime;

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePosition = GetMousePosition();
    int targetX = mousePosition.x / game.settings.gridWidth;
    int targetY = mousePosition.y / game.settings.gridHeight;

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
    findShortestPath(game, player->x, player->y, targetX, targetY);
    if (!pathQueue.empty()) {
      // reset move timer for smoother transition?
      deltaTimeSinceLastMove = 0;
    }
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      game.changeState("combat");
      break;
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
      int targetX = player->x;
      int targetY = player->y;

      if (player->facing == "up") {
        targetY--;
      }
      else if (player->facing == "down") {
        targetY++;
      }
      else if (player->facing == "left") {
        targetX--;
      }
      else if (player->facing == "right") {
        targetX++;
      }
      else {
        fprintf(stderr, "invalid player->facing direction");
        return;
      }

      for (Entity* entity : entities) {
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

  int newX = player->x;
  int newY = player->y;
  std::string direction = inputHelper(player->facing);

  if (direction == "none") {
    // Continue moving along the path until the queue is empty
    while (!pathQueue.empty()) {
      if (deltaTimeSinceLastMove < moveSpeed) {
        break; // Too soon for another move
      }
      std::pair<int, int> nextPos = pathQueue.front();
      pathQueue.pop();
      player->move(nextPos.first, nextPos.second);
      lastMoveTime = currentTime;
      break;
    }
    return;
  }
  else if (direction == "right") {
    player->facing = "right";
    newX++;
  }
  else if (direction == "left") {
    player->facing = "left";
    newX--;
  }
  else if (direction == "down") {
    player->facing = "down";
    newY++;
  }
  else if (direction == "up") {
    player->facing = "up";
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
    newX >= columns ||
    newY < 0 ||
    newY >= rows;
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
  else if (grid[newX][newY] == 1) {
    // no movement, terrain or tile block
    return;
  }
  else if (newY != 0){
    // NOTE: player's depth/y changed, so we need to sort the GameObjects vector
    sortGameObjects();
    player->move(newX, newY);
    lastMoveTime = currentTime;
  }
  else {
    player->move(newX, newY);
    lastMoveTime = currentTime;
  }
}

std::string World::inputHelper(std::string facing) {
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
void World::findShortestPath(Game& game, int startX, int startY, int targetX, int targetY) {
  std::pair<int, int> start = { startX, startY};
  std::pair<int, int> target = { targetX, targetY};
  int dx[] = {1, -1, 0, 0};  // Possible movements in x-direction
  int dy[] = {0, 0, 1, -1};  // Possible movements in y-direction
  std::vector<std::vector<std::pair<int, int>>> parent(20, std::vector<std::pair<int, int>>(12, {-1, -1}));
  std::queue<std::pair<int, int>> q;
  q.push(start);

  if (grid[targetX][targetY] != 0) {
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
        grid[newX][newY] == 0;

      if (isValid && parent[newX][newY].first == -1) {
        q.push({newX, newY});
        parent[newX][newY] = curr;
      }
    }
  }

  fprintf(stderr, "No path found!\n");
}



