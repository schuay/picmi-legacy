/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picpoint.h"

PicPoint::PicPoint() {
    x = 0;
    y = 0;
}
PicPoint::PicPoint(PicPoint *p) {
    x = p->x;
    y = p->y;
}
PicPoint::PicPoint(unsigned int _x, unsigned int _y)
{
    x = _x;
    y = _y;
}

bool PicPoint::operator==(PicPoint const &p) {
    return ((this->x == p.x) && (this->y == p.y));
}
bool PicPoint::operator!=(PicPoint const &p) {
    return ((this->x != p.x) || (this->y != p.y));
}
PicPoint& PicPoint::operator=(PicPoint const &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;

    return *this;
}
