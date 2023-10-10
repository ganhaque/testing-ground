#include "Combat.h"

void Combat::render(Game& game) {
  // TODO:
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  EndDrawing();
}

void Combat::processInput(Game& game) {
  // TODO:
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      if (currentUnitIndex < units.size()) {
        Unit& currentPlayer = units[currentUnitIndex];
        if (!currentPlayer.hasTakenTurn) {
          // Handle player's turn (e.g., wait for user input like Space key press)
          currentPlayer.passTurn();
          currentUnitIndex++;
        }
      }
      else {
        startRound();
      }
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      if (!game.dialogQueue.empty()) {
        game.dialogQueue.pop();
        break;
      }
      break;
  }
  return;
}

void Combat::startRound() {
  fprintf(stderr, "round %d started\n", currentRound);
  currentRound++;
  isRoundOver = false;
  for (Unit& unit : units) {
    unit.hasTakenTurn = false;
  }
  // for (Unit& unit : enemies) {
  //   unit.hasTakenTurn = false;
  // }

  std::sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
      return a.initiative > b.initiative;
      });
  currentUnitIndex = 0; // Start with the first player character
}

void Combat::update(Game& game) {
}

void Combat::initialize() {
  currentRound = 0;
  units = {};
  units.push_back(Unit("unit1", 1, 1, 1));
  units.push_back(Unit("unit2", 1, 1, 3));
  units.push_back(Unit("unit3", 1, 1, 7));
  std::sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
      return a.initiative > b.initiative;
      });
}

void Combat::exit() {}

Combat::~Combat() {
  return;
}
