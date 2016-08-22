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
    if(x < p.x) return true;
    if(p.x < x) return false;
    return y < p.y;
}

bool Point::operator==(const Point& p) const
{
    return x == p.x && y == p.y;
}

bool Point::operator!=(const Point &p) const
{
    return x != p.x || y != p.y;
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
    }

}
