#include <iostream>
#include <string>
#include <vector>

class Tile {
  public:
    Tile(bool interactable, bool blockMovement, const std::string& dialogueId)
      : interactable_(interactable), blockMovement_(blockMovement), dialogueId_(dialogueId) {
      }

    bool isInteractable() const {
      return interactable_;
    }

    bool blocksMovement() const {
      return blockMovement_;
    }

    const std::string& getDialogueId() const {
      return dialogueId_;
    }

  private:
    bool interactable_;
    bool blockMovement_;
    std::string dialogueId_;
};

class ChestTile : public Tile {
  public:
    ChestTile()
      : Tile(true, true, ""), contents_({"1-Health_Pot"}) {
      }

    const std::vector<std::string>& getContents() const {
      return contents_;
    }

  private:
    std::vector<std::string> contents_;
};

class NpcTile : public Tile {
  public:
    NpcTile()
      : Tile(true, true, "") {
      }
};

class BattleTile : public Tile {
  public:
    BattleTile()
      : Tile(true, true, "") {
      }
};

class TerrainTile : public Tile {
  public:
    TerrainTile()
      : Tile(false, true, "") {
      }
};

class TransitionTile : public Tile {
  public:
    TransitionTile(const std::string& destinationRoomId)
      : Tile(false, false, ""), destinationRoomId_(destinationRoomId) {
      }

    const std::string& getDestinationRoomId() const {
      return destinationRoomId_;
    }

  private:
    std::string destinationRoomId_;
};

int main() {
  ChestTile chestTile;
  NpcTile npcTile;
  BattleTile battleTile;
  TerrainTile terrainTile;
  TransitionTile transitionTile("nextRoom");

  std::cout << "Chest Tile: Interactable = " << chestTile.isInteractable()
    << ", Blocks Movement = " << chestTile.blocksMovement()
    << ", Dialogue ID = " << chestTile.getDialogueId() << std::endl;

  std::cout << "Transition Tile: Interactable = " << transitionTile.isInteractable()
    << ", Blocks Movement = " << transitionTile.blocksMovement()
    << ", Destination Room ID = " << transitionTile.getDestinationRoomId() << std::endl;

  return 0;
}
