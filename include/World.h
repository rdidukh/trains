#pragma once

#include "Rail.h"
#include "Train.h"

class World
{
public:
    Rail * addRail(int x1, int y1, int x2, int y2);
    Rail * addRail(Rail * rail);
    void addTrain(Train & train);
    void moveTrain(Train * train, float dTime);
    void updateTrain(Train * train, float dTime);
    ~World();

    void update(float dTime);

    std::vector<Rail*>::iterator railsBegin();
    std::vector<Rail*>::iterator railsEnd();

private:
    float time;
    std::vector<Rail *> rails;
    std::set<Rail* > allocRails;
    std::map<Point, std::vector<Splice>> points;
    std::vector<Train *> trains;
};
