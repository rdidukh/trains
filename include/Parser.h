#pragma once

#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>

#include "World.h"
#include "Rail.h"

class Parser
{
public:
    Parser(World & world);
    bool parse(std::istream & is);
    std::string error();
private:

    struct ParserRail
    {
        std::string id;
        std::vector<float> points;
    };

    World & world;
    Json::Value root;
    std::ostringstream errStr;
    bool parseRails(Json::Value obj, std::vector<ParserRail> &parserRails);
    bool parseRail(Json::Value obj, ParserRail & rail);
    bool parsePoints(Json::Value obj, std::vector<float> & points);
    bool parsePointsArrays(Json::Value obj, std::vector<float> & points);
    bool parsePointsFloats(Json::Value obj, std::vector<float> & points);
    std::vector<Rail *> rails;
};
