#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "Rail.h"

class World
{
    std::vector<Rail> rails;

public:
    void init();
    void update(int frame);
    void addRail(const Rail & rail);
    bool read(std::istream & is);
};
