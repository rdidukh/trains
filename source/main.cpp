#include <iostream>

#include "World.h"
#include "Train.h"
#include "OpenGL.h"

int main(int argc, char * argv[])
{
    World world;

    Rail * rail = world.addRail(0, 0, 100, 0);

    Train train;
    train.head = {rail, 10};
    train.length = 10;
    train.speed = 10;

    world.addTrain(train);

    OpenGL openGL(world);

    openGL.run(10);

    return 0;
}

