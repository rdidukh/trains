#pragma once

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <cmath>
#include <array>
#include <functional>

struct Point
{
    float x;
    float y;
    float dist(const Point & p) const;
    bool operator<(const Point & point) const;
    bool operator==(const Point & point) const;
    bool operator!=(const Point & point) const;
    constexpr static float error() { return 0.001f; }
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
    Rail(float x1, float y1, float x2, float y2);

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
    float advanceToPoint(float distance);

    Point point();
};

bool operator<(const Rail & a, const Rail & b);
std::ostream & operator<<(std::ostream & os, Rail & rail);

