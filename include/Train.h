#pragma once

#include "Rail.h"

#include <vector>

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
