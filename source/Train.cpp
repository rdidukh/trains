#include "Train.h"



Train::Train()
{

}


void Train::polyline(Func func)
{
    float sub = length;
    Position pos = head;
    int index = 0;
    func(pos.point(), index++);
    while(sub != 0.0)
    {
        sub = pos.advanceToPoint(sub);
        func(pos.point(), index++);
    }
}
