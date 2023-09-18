#include "raylib.h"
#include <ctime>

enum class Direction : char {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3
};

class Coordinate {
  public:
    int x;
    int y;
};

class Stats {
  public:
    int level;
    int maxHp;
    int atkDmg;
    int abilityPower;
    int armor;
};

class Character {
  private:
    // TODO: move data members to private after making getter functions
  public:
    Coordinate position;
    Stats stats;
    Direction facing;

    Character(int startX, int startY) : position{startX, startY}, facing(Direction::DOWN) {}

    void move(int newX, int newY) {
      position.x = newX;
      position.y = newY;
    }

    // void interact(Object& object) {
    //   // TODO:
    // }
};

class Game {
  public:
    // const int screenWidth = 800;
    // const int screenHeight = 600;
    // const int gridSize = 50;
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    // const int gridSize = 100;
    const int gridSize = 50;

    Character player;
    bool objectExists;
    int objectX;
    int objectY;
    // int grid[16][10];
    int grid[16*2][10*2];

    // Time variables for controlling movement speed
    double lastMoveTime;
    double moveSpeed = 0.1;

    Game() : player(1, 1), objectExists(true), objectX(2), objectY(2) {
      // Initialize grid (adjust size accordingly)
      for (int x = 0; x < screenWidth / gridSize; x++) {
        for (int y = 0; y < screenHeight / gridSize; y++) {
          grid[x][y] = (x == 2 && y == 3) ? 1 : 0; // Set an obstacle
        }
      }
    }

    void HandleUserInput() {
      const double currentTime = GetTime();
      const double deltaTime = currentTime - lastMoveTime;

      if (deltaTime < moveSpeed) {
        return; // Too soon for another move
      }

      int newX = player.position.x;
      int newY = player.position.y;

      if (IsKeyDown(KEY_RIGHT)) {
        newX++;
        player.facing = Direction::RIGHT;
      }
      else if (IsKeyDown(KEY_LEFT)) {
        newX--;
        player.facing = Direction::LEFT;
      }
      else if (IsKeyDown(KEY_DOWN)) {
        newY++;
        player.facing = Direction::DOWN;
      }
      else if (IsKeyDown(KEY_UP)) {
        newY--;
        player.facing = Direction::UP;
      }
      else if (IsKeyPressed(KEY_SPACE)) {
        // Interact with object

        // if (TryRemoveObject(player.facing)) {
        //   objectExists = false;
        // }
      }

      if (isValidMove(newX, newY)) {
        player.move(newX, newY);
        lastMoveTime = currentTime;
      }
    }

    bool isValidMove(int newX, int newY) {
      return (newX >= 0 && newX < (screenWidth / gridSize) && newY >= 0 && newY < (screenHeight / gridSize) && grid[newX][newY] == 0);
    }


    void run() {
      InitWindow(screenWidth, screenHeight, "Grid-Based Movement with Interactive Objects");

      SetTargetFPS(60);

      while (!WindowShouldClose()) {
        HandleUserInput();

        BeginDrawing();
        // ClearBackground(RAYWHITE);
        ClearBackground(BLACK);

        // Draw the grid
        for (int x = 0; x < screenWidth; x += gridSize) {
          for (int y = 0; y < screenHeight; y += gridSize) {
            if (grid[x / gridSize][y / gridSize] == 1) {
              DrawRectangle(x, y, gridSize, gridSize, DARKGRAY);
            }
            else {
              DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
            }
          }
        }

        // Draw the interactive object (pot or chest)
        if (objectExists) {
          DrawRectangle(objectX * gridSize, objectY * gridSize, gridSize, gridSize, BLUE);
        }

        // Draw the player character
        DrawRectangle(player.position.x * gridSize, player.position.y * gridSize, gridSize, gridSize, RED);

        EndDrawing();
      }

      CloseWindow();
    }
};

int main() {
  Game game;
  game.run();
  return 0;
}

