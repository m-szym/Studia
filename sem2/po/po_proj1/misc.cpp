#include "misc.h"





XY::XY(int x, int y)
    : x(x), y(y)
{}

bool XY::operator==(XY other)
{
    if (this->x == other.x && this->y == other.y)
        return true;
    else
        return false;
}

std::string XY::to_string()
{
    std::string xy(" (");
    xy += std::to_string(this->x);
    xy += ", ";
    xy += std::to_string(this->y);
    xy += ") ";
    return xy;
}



