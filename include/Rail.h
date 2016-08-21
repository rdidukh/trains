#pragma once

#include <set>
#include <map>
#include <vector>
#include <iostream>

struct Point
{
    int x;
    int y;
};

bool operator<(const Point & a, const Point & b);

struct Rail;

struct Splice
{
    Splice(): rail(nullptr), end(-1) {}
    Splice(Rail * r, int e): rail(r), end(e) {}

    Rail * rail;
    int end;
};

struct Rail
{
    Rail(int x1, int y1, int x2, int y2)
    {
        point[0] = { x1, y1 };
        point[1] = { x2, y2 };
    }

    Rail * next(int end)
    {
        return splice[end].rail;
    }

    Point point[2];
    Splice splice[2];
};

bool operator<(const Rail & a, const Rail & b);

std::ostream & operator<<(std::ostream & os, Rail & rail);

struct Position
{
    Rail * rail;
    float offset;
};

Position operator+(const Position & pos, float rhs);
