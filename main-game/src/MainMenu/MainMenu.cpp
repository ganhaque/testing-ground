#include "MainMenu.h"
#include <cstdio>
#include <raylib.h>

void MainMenu::render(Game& game) {
  BeginDrawing();
  // TODO: put your render for start menu/screen here

  // placeholder, to be replaced
  DrawText(
      "Press Space to Continue or something idk",
      game.settings.screenWidth / 2 - 50,
      game.settings.screenHeight / 2, 20,
      RAYWHITE
      );
  EndDrawing();
}

void MainMenu::processInput(Game& game) {
  if (IsKeyPressed(KEY_SPACE)) {
    game.changeState("world");
    // game.changeState("combat");
  }
}

void MainMenu::update(Game& game) {
}

MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
  return;
}
