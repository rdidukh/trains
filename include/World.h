#pragma once

#include "Rail.h"
#include "Train.h"

class World
{
public:
    Rail * addRail(int x1, int y1, int x2, int y2);
    ~World();
private:
    std::vector<Rail *> rails;
    std::map<Point, std::vector<Splice>> points;
};
