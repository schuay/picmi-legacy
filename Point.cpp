#include "Point.h"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(unsigned int _x, unsigned int _y)
{
    x = _x;
    y = _y;
}

bool Point::operator==(Point const &p) {
    return ((this->x == p.x) && (this->y == p.y));
}

bool Point::operator!=(Point const &p) {
    return ((this->x != p.x) || (this->y != p.y));
}

Point& Point::operator=(Point const &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
}
