#pragma once

#include "Rail.h"
#include "Train.h"

class World
{
public:
    Rail * addRail(int startX, int startY, int endX, int endY);
    ~World();
private:
    std::vector<Rail *> rails;
    std::map<Point, std::vector<Splice>> points;
};
