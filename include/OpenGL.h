#pragma once

#include "World.h"

#include <vector>

class OpenGL
{
public:
    OpenGL(World & world);
    void run(unsigned fps);
private:
    World & world;
    float minX = 0.0f;
    float maxX = 1.0f;
    float minY = 0.0f;
    float maxY = 1.0f;

    static OpenGL * openGL;
    static void display_static();
    static void timer_static(int);
    static void reshape_static();
    void display();
    void timer(int ms);
    std::vector<float> rails;
    std::vector<float> trains;
};
