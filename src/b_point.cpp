/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#include "b_point.h"

namespace BoardGame {
Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(Point const *p) {
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
}
