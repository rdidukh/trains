#pragma once

#include "World.h"

class OpenGL
{

public:
    OpenGL(World & world);
    void run(unsigned fps);
private:
    World & world;
    static OpenGL * openGL;
    static void display_static();
    static void timer_static(int);
    static void reshape_static();
    void display();
};
