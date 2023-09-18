#include <iostream>
#include <fstream>
#include <json/json.h>

int main() {
  // Create a JSON parser
  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string errs;

  // Read the JSON data from a file
  std::ifstream jsonFile("00-00.json");
  if (parseFromStream(builder, jsonFile, &root, &errs)) {
    // JSON parsing succeeded
    std::cout << "Parsing succeeded." << std::endl;

    // Now you can access the data in 'root' as needed
    std::string roomID = root["roomID"].asString();
    std::string roomName = root["roomName"].asString();

    // Print the room information
    std::cout << "Room ID: " << roomID << std::endl;
    std::cout << "Room Name: " << roomName << std::endl;

    // Accessing the specialTiles array
    Json::Value specialTiles = root["specialTiles"];
    for (int i = 0; i < specialTiles.size(); i++) {
      Json::Value tile = specialTiles[i];
      int x = tile["x"].asInt();
      int y = tile["y"].asInt();
      std::string type = tile["type"].asString();

      // Print tile information
      std::cout << "Tile " << i << ":" << std::endl;
      std::cout << "  x: " << x << ", y: " << y << std::endl;
      std::cout << "  type: " << type << std::endl;

      // Handle different types of tiles accordingly
      if (type == "transition") {
        std::string destinationRoomID = tile["destinationRoomID"].asString();
        // Handle transition tile
        std::cout << "  destinationRoomID: " << destinationRoomID << std::endl;
      } else if (type == "npc") {
        std::string dialogue = tile["dialogue"].asString();
        // Handle npc tile
        std::cout << "  dialogue: " << dialogue << std::endl;
      } else if (type == "chest") {
        // Handle chest tile
      } else if (type == "battle") {
        // Handle battle tile
      } else if (type == "terrain") {
        // Handle terrain tile
      }

      // You can access other properties as needed
    }
  } else {
    // JSON parsing failed, print error message
    std::cerr << "Parsing failed: " << errs << std::endl;
  }

  return 0;
}

