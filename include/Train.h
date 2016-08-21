#pragma once

#include "Rail.h"

class Train
{
public:

private:

    enum class State
    {
        Idle,
    };

    Position head;
    float length;
    float speed;
    State state;
};
