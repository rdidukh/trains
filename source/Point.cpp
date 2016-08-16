#include "Point.h"

std::istream & operator>>(std::istream & is, Point & point)
{
    int x, y;
    is >> x >> y;
    point.x = x;
    point.y = y;
    return is;
}
