// StringParser.h
#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include <string>
#include <vector>

class StringParser {
  public:
    static void ParseString(const std::string& input, int& intValue, std::string& stringValue);
    static void ParseCoordinate(const std::string& input, int& firstInt, int& secondInt);
};

#endif // STRING_PARSER_H

