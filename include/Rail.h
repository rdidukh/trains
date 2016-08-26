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
    bool operator<(const Rail & a) const;

    std::array<Point,  2> point;
    std::array<Splice, 2> splice;
    float length;
};

struct Interval
{
    Interval(Rail * r, float s, float e);
    Rail * rail;
    float start;
    float end;
    bool operator<(const Interval & ival) const;
};

struct Position
{
    Position(Rail * r = nullptr, float off = 0);

    float advance(float distance);
    float advanceToPoint(float distance);
    Interval interval(float distance);
    Point point();

    Rail * rail;
    float offset;
};


std::ostream & operator<<(std::ostream & os, Rail & rail);

