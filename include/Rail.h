#pragma once

#include "Point.h"

struct Rail
{
    Point start;
    Point end;
};

std::istream & operator>>(std::istream & is, Rail & rail);
