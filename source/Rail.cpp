#include "Rail.h"

std::istream & operator>>(std::istream & is, Rail & rail)
{
    is >> rail.start;
    is >> rail.end;
    return is;
}
