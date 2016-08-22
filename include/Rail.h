#pragma once

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <cmath>
#include <array>

struct Point
{
    int x;
    int y;
    float dist(const Point & p) const;
    bool operator<(const Point & point) const;
    bool operator==(const Point & point) const;
    bool operator!=(const Point & point) const;
};

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
    Rail(int x1, int y1, int x2, int y2);

    Rail * next(int end) const;
    static bool connect(Rail * railA, Rail * railB);

    std::array<Point,  2> point;
    std::array<Splice, 2> splice;
    float length;
};


struct Position
{
    Position(Rail * r = nullptr, float off = 0);
    Rail * rail;
    float offset;
    void advance(float distance);
    /*
     * TODO:
     *  Point point();
     */
};

bool operator<(const Rail & a, const Rail & b);
std::ostream & operator<<(std::ostream & os, Rail & rail);

