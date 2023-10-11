// GameObject.h
#pragma once

#include <raylib.h>
#include <string>

class Entity {
  public:
    std::string id;
    int x;
    int y;

    // TODO: use this to render
    int offsetX = 0;
    int offsetY = 0;
    Texture2D sprite;

    // TODO: maybe add parameter such as scaling because
    // that is necessary for rendering correctly when resizing
    virtual void render(int gridWidth, int gridHeight) = 0;
};
