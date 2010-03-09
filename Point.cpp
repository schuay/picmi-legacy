/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Point.h"

Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(Point *p) {
    x = p->x;
    y = p->y;
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

    return *this;
}
