#pragma once

#include "Rail.h"

class Train
{
public:
    Position head;
    float speed;
    float length;
    Train();
private:

    enum class State
    {
        Idle,
    };

    State state;
};
