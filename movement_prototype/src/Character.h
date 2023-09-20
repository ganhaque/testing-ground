// Character.h
#include "raylib.h"

#pragma once
// #include "Stats.h"

class Stats {
  public:
    Rectangle characterRect; // Add this member variable
    int level;
    int maxHp;
    int atkDmg;
    int abilityPower;
    int armor;
};


enum class Direction : int {
  LEFT = 0,
  DOWN = 1,
  UP = 2,
  RIGHT = 3,
};

class Character {
  private:
    // TODO: move data members to private after making getter functions
  public:
    Texture2D texture;
    Rectangle frameRects[4]; // One rectangle for each animation frame (down, up, left, right)
    int currentFrame; // To keep track of the current frame
    int x;
    int y;
    Stats stats;
    Direction facing;

    Character(int startX, int startY);

    void move(int newX, int newY);
    void draw(int gridSize);
    void updateAnimation();
};
