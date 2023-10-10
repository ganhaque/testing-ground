// Helper.h
#pragma once
#include <raylib.h>
#include <string>

// NOTE: Helper to parse strings/id & other stuffs to make thing more
// convenient.
// NOTE: because of the 'static' keyword, all functions
// can be called without creating a class instance by Helper::functionName(...)

class Helper {
  public:
    static Texture2D loadTexture(std::string filePath);
    static void parseString(const std::string& input, int& intValue, std::string& stringValue);
    static void parseCoordinate(const std::string& input, int& firstInt, int& secondInt);
    static std::string parseGameObjectType(const std::string& input);
};
