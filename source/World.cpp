#include "World.h"

#include <memory>

#include <Assert.h>

World::~World()
{
    for(Rail * rail : allocRails)
    {
        delete rail;
    }
}

Rail * World::addRail(int x1, int y1, int x2, int y2)
{
    if(x1 == x2 && y1 == y2) return nullptr;
    /* TODO: check rail for correctness(intersection, overlap, etc) */

    std::unique_ptr<Rail> rail(new Rail(x1, y1, x2, y2));

    std::vector<std::pair<Splice, int>> update;

    for(int i = 0; i <= 1; i++)
    {
        Point & point = rail->point[i];

        if(points.count(point))
        {
            auto & splices = points[point];

            ASSERT(!splices.empty());

            if(splices.size() == 1)
            {
                Splice & splice = splices[0];

                ASSERT(splice.rail);

                if(splice.rail->next(splice.end) == nullptr)
                {
                    update.emplace_back(splice, i);
                }
                if(rail->next(i) == nullptr)
                {
                    rail->splice[i] = splice;
                }
            }
            else if(splices.size() == 2)
            {
                /* TODO: switch */
                return nullptr;
            }
        }
    }

    rails.push_back(rail.get());

    for(int i = 0; i <= 1; i++)
        points[rail->point[i]].emplace_back(rail.get(), i);

    for(auto & p : update)
    {
        Splice & sp = p.first;
        int end = p.second;
        sp.rail->splice[p.first.end] = {rail.get(), end};
    }

    allocRails.insert(rail.get());

    return rail.release();
}

Rail *World::addRail(Rail *rail)
{
    return nullptr;
}

void World::addTrain(Train& train)
{
    trains.push_back(&train);
}

void World::moveTrain(Train *train, float dTime)
{
    train->head.advance(dTime * train->speed);
}

void World::updateTrain(Train *train, float dTime)
{
    train->speed += dTime * 0;
}

void World::update(float dTime)
{
    for(Train * train : trains)
    {
        moveTrain(train, dTime);
        updateTrain(train, dTime);
    }

    time += dTime;
}
