#include "raylib.h"

#pragma once

class Sprite2D {
  private:
    Texture2D texture;
    Rectangle frameRects[4];
    int currentFrame = 0;
    // int x;
    // int y;

    // MAYBE: ?
    bool flipVertical;
    bool flipHorizontal;

  public:
    Sprite2D(const char* imagePath);

    void move(int newX, int newY);
    void draw(int x, int y, int gridSize);
};
