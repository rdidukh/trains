#include "Rail.h"

#include <iostream>
#include <memory>
#include <cassert>

Rail::Rail(int x1, int y1, int x2, int y2)
{
    point[0] = { x1, y1 };
    point[1] = { x2, y2 };
    length = point[0].dist(point[1]);
}

Rail * Rail::next(int end) const
{
    return splice[end].rail;
}

std::ostream & operator<<(std::ostream & os, Rail & rail)
{
    os << "[" << rail.point[0].x << ", " << rail.point[0].y << ", " << rail.point[1].x << ", " << rail.point[1].y << "]";
    return os;
}

bool operator<(const Rail & a, const Rail & b)
{
    if(a.point[0] < b.point[0]) return true;
    if(b.point[0] < a.point[0]) return false;
    return a.point[1] < b.point[1];
}

bool operator<(const Point & a, const Point & b)
{
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    return a.y < b.y;
}

Position operator+(const Position & pos, float rhs)
{
    return {nullptr, 0.0f};
}


float Point::dist(const Point &p) const
{
    return sqrtf((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
}
