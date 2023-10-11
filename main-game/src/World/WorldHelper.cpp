#include "World.h"

void World::resetGrid() {
  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 12; y++) {
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
}

// Should be called whenever entities changes or existing entities change their y position
void World::sortGameObjects() {
  // NOTE: Sort player and tile/object based on their y (depth)
  // THEN: Iterate & call render for player and object
  // NOTE: This is necessary because the sprite of whatever would not
  // fit the 96x80 grid, so the object with lower y (farther away) will
  // render before object closer
  // basically, if player is in front of the chest, the chest sprite would not
  // appear over the player
  // and vice versa,
  // if player is behind, the player sprite would not appear over the chest
  std::sort(
      entities.begin(),
      entities.end(),
      [](const Entity* a, const Entity* b) {
      return a->y < b->y;
      });
}
