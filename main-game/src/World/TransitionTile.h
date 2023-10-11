#include <string>

class TransitionTile {
  public:
    int x, y;
    int enterX, enterY;
    std::string destinationRoomId;

    TransitionTile(
        int x,
        int y,
        int enterX,
        int enterY,
        const std::string& destinationRoomId
        ) :
      x(x),
      y(y),
      enterX(enterX),
      enterY(enterY),
      destinationRoomId(destinationRoomId) {}

    // You can add more methods and properties if needed
};

// TODO: Transitontile implmentation
// When player is standing on 
