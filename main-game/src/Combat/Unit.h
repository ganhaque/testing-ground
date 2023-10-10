#pragma once
#include <string>

class Unit {

  public:
    std::string name;
    int health;
    int damage;
    int initiative;
    bool hasTakenTurn;

    Unit(
        std::string name,
        int health,
        int damage,
        int initiative
        ) :
      name(name),
      health(health),
      damage(damage),
      hasTakenTurn(false),
      initiative(initiative) {}

    void passTurn() {
      // Implement logic to pass the turn
      hasTakenTurn = true;
      fprintf(stderr, "Character %s passed their turn\n", name.c_str());
    }
};
