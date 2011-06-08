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

#include "b_draghelper.h"

namespace BoardGame {

DragHelper::DragHelper() {
    reset();
    lockToLine = true;
}

void DragHelper::reset() {
    button = sf::Mouse::ButtonCount;
    direction = DRAG_UNDEF;
    posChanged = false;
}

void DragHelper::begin(sf::Vector2i pos, sf::Mouse::Button button, int op) {
    lastClick = pos;
    last = pos;
    this->button = button;
    dragOp = op;
    posChanged = false;
}

sf::Vector2i DragHelper::update(sf::Vector2i pos) {
    if (pos != lastClick && direction == DRAG_UNDEF ) { /* calc drag direction */
        unsigned int diffX = abs(lastClick.x - pos.x);
        unsigned int diffY = abs(lastClick.y - pos.y);
        if (diffX < diffY) {
            direction = DRAG_VERTICAL;
        } else {
            direction = DRAG_HORIZONTAL;
        }
    }

    if (!lockToLine) {
        /* skip line locking */
    } else if (direction == DRAG_HORIZONTAL) {  /* adjust newLocation according to dragDirection */
        pos.y = lastClick.y;
    } else if (direction == DRAG_VERTICAL) {
        pos.x = lastClick.x;
    }

    if (last != pos) {
        last = pos;
        posChanged = true;
    } else {
        posChanged = false;
    }

    return pos;
}

}
