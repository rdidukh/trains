#include "Rail.h"

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

