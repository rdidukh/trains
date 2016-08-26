#include "Rail.h"

#include <iostream>
#include <memory>
#include <Assert.h>

Rail::Rail(float x1, float y1, float x2, float y2)
{
    point[0] = { x1, y1 };
    point[1] = { x2, y2 };
    length = point[0].dist(point[1]);
}

Rail * Rail::next(int end) const
{
    return splice[end].rail;
}

bool Rail::connect(Rail *railA, Rail *railB)
{
    if(railA == nullptr) return false;
    if(railB == nullptr) return false;

    int endA, endB;

    for(endA = 0; endA <= 1; endA++)
        for(endB = 0; endB <=1; endB++)
            if(railA->point[endA] == railB->point[endB])
            {
                railA->splice[endA] = {railB, endB};
                railB->splice[endB] = {railA, endA};
                return true;
            }

    return false;
}

std::ostream & operator<<(std::ostream & os, Rail & rail)
{
    os << "[" << rail.point[0].x << ", " << rail.point[0].y << ", " << rail.point[1].x << ", " << rail.point[1].y << "]";
    return os;
}

bool Rail::operator<(const Rail & rail) const
{
    if(point[0] < rail.point[0]) return true;
    if(rail.point[0] < point[0]) return false;
    return point[1] < rail.point[1];
}

bool operator<(const Point & a, const Point & b)
{
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    return a.y < b.y;
}

float Point::dist(const Point &p) const
{
    return sqrtf((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
}

bool Point::operator<(const Point& p) const
{
    int64_t ix = static_cast<int64_t>(x/error()+0.5f);
    int64_t iy = static_cast<int64_t>(y/error()+0.5f);
    int64_t pix = static_cast<int64_t>(p.x/error()+0.5f);
    int64_t piy = static_cast<int64_t>(p.y/error()+0.5f);

    if(ix < pix) return true;
    if(pix < ix) return false;
    return iy < piy;
}

bool Point::operator==(const Point& p) const
{
    return std::fabs(x - p.x) <= error() && std::fabs(y - p.y) <= error();
}

bool Point::operator!=(const Point &p) const
{
    return std::fabs(x - p.x) >= error() || std::fabs(y - p.y) >= error();
}

Position::Position(Rail *r, float off):
    rail(r), offset(off)
{

}


float Position::advance(float d)
{
    float ret = std::copysignf(1.0f, d);
    while(d != 0.0)
    {
        ret = std::copysignf(1.0f, d);
        d = advanceToPoint(d);
    }

    return ret;
}

float Position::advanceToPoint(float distance)
{
    if(rail == nullptr) return 0.0;
    offset += distance;
    float ret = 0.0;

    if(offset <= 0.0f)
    {
        if(rail->splice[0].end == 0)
        {
            ret = -offset;
            offset = 0.0f;
        }
        else if(rail->next(0) != nullptr)
        {
            ret = offset;
            offset = rail->next(0)->length;
        }
        rail = rail->next(0);
    }
    else if(offset >= rail->length)
    {
        offset -= rail->length;
        if(rail->splice[1].end == 0)
        {
            ret = offset;
            offset = 0.0f;
        }
        else if(rail->next(1) != nullptr)
        {
            ret = -offset;
            offset = rail->next(1)->length;
        }
        rail = rail->next(1);
    }

    return ret;
}

Interval::Interval(Rail* r, float s, float e):
    rail(r), start(s), end(e)
{

}

Interval Position::interval(float distance)
{
    float off = offset + distance;
    off = std::max(off, 0.0f);
    off = std::min(off, rail->length);
    float start = std::min(offset, off);
    float end   = std::max(offset, off);

    return Interval(rail, start, end);
}

Point Position::point()
{
    ASSERT(rail);
    float x1 = rail->point[0].x;
    float y1 = rail->point[0].y;
    float x2 = rail->point[1].x;
    float y2 = rail->point[1].y;
    float x = x1 + (x2 - x1) * offset / rail->length;
    float y = y1 + (y2 - y1) * offset / rail->length;
    return {x, y};
}


