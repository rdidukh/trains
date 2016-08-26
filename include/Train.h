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

    using Func = std::function<void(const Point &, int)>;

    void polyline(Func func);

private:

    enum class State
    {
        Idle,
    };

    State state;
};
