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

float Point::dist(const Point &p) const
{
    return sqrtf((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
}

bool Point::operator<(const Point& p) const
{
    int64_t ix = static_cast<int64_t>(x/error+0.5f);
    int64_t iy = static_cast<int64_t>(y/error+0.5f);
    int64_t pix = static_cast<int64_t>(p.x/error+0.5f);
    int64_t piy = static_cast<int64_t>(p.y/error+0.5f);

    if(ix < pix) return true;
    if(pix < ix) return false;
    return iy < piy;
}

bool Point::operator==(const Point& p) const
{
    return std::fabs(x - p.x) < error && std::fabs(y - p.y) < error;
}

bool Point::operator!=(const Point &p) const
{
    return std::fabs(x - p.x) >= error || std::fabs(y - p.y) >= error;
}

Position::Position(Rail *r, float off):
    rail(r), offset(off)
{

}


void Position::advance(float d)
{
    offset += d ;

    while(rail && (offset < 0 || offset > rail->length))
    {
        offset -= offset > 0 ? rail->length : 0.0;
        int end = static_cast<int>(std::copysign(0.5, offset) + 0.5);

        if(rail->splice[end].end == 0)
        {
            offset = std::fabs(offset);
        }
        else if(rail->next(end) != nullptr)
        {
            offset = rail->next(end)->length - std::fabs(offset);
        }
        rail = rail->next(end);
#if 0
        if(offset > rail->length)
        {
            offset -= rail->length;
            if(rail->splice[1].end == 0)
            {
                offset = offset;
            }
            else if(rail->splice[1].rail != nullptr)
            {
                offset = rail->next(1)->length - offset;
            }
            rail = rail->next(1);
        }
        else if(offset < 0)
        {
            offset -= 0;
            if(rail->splice[0].end == 0)
            {
                offset = -offset;
            }
            else if(rail->splice[0].rail != nullptr)
            {
                offset = rail->next(0)->length + offset;
            }
            rail = rail->next(0);
        }
#endif
    }
}

template<class Func>
void Position::polyline(float distance)
{

}

Point Position::point()
{
    ASSERT(rail);
    float x = rail->point[0].x;
    float y = rail->point[0].y;
    return {x, y};
}


