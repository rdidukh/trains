#pragma once

#include <set>
#include <map>

struct Point
{
    int x;
    int y;
};

bool operator<(const Point & a, const Point & b);

struct Rail
{
    Point start;
    Point end;
    Rail * prev;
    Rail * next;
};

struct Position
{
    Rail * rail;
    float offset;
};

Position operator+(const Position & pos, float rhs);

class RailNetwork
{
    public:
    RailNetwork();
    Rail * addRail(int startX, int startY, int endX, int endY);

    private:
//    std::vector<Rail> rails;
//    std::map<Point, std::vector<Rail *>> points;
};

