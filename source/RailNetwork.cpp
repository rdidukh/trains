#include "Rail.h"

#include <iostream>
#include <cassert>

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

RailNetwork::RailNetwork()
{

}

RailNetwork::~RailNetwork()
{
    for(Rail * rail : rails)
    {
        delete rail;
    }
}

Rail * RailNetwork::addRail(int x1, int y1, int x2, int y2)
{   
    if(x1 == x2 && x2 == y2) return nullptr;
    /* TODO: check rail for correctness(intersection, overlap, etc) */

    Rail rail(x1, y1, x2, y2);

    std::vector<std::pair<Splice, int>> update;

    for(int i = 0; i <= 1; i++)
    {
        Point & point = rail.point[i];

        if(points.count(point))
        {
            auto & splices = points[point];

            assert(!splices.empty());

            if(splices.size() == 1)
            {
                Splice & splice = splices[0];

                assert(splice.rail);

                if(splice.rail->next(splice.end) == nullptr)
                {
                    update.emplace_back(splice, i);
                }

                if(rail.next(i) == nullptr)
                {
                    rail.splice[i] = splice;
                }
            }
            else if(splices.size() == 2)
            {
                /* TODO: switch */
                return nullptr;
            }
        }
    }

    Rail * railPtr = new Rail(rail);

    rails.push_back(railPtr);

    for(int i = 0; i <= 1; i++)
        points[rail.point[0]].push_back(railPtr->splice[i]);

    for(auto & p : update)
    {
        Splice & sp = p.first;
        int end = p.second;
        sp.rail->splice[p.first.end] = {railPtr, end};
    }

    return railPtr;
}
