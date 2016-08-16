#pragma once

#include <iostream>

struct Point
{
    int x;
    int y;
};

std::istream & operator>>(std::istream & is, Point & point);
