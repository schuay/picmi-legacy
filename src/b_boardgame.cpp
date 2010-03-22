/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_boardgame.h"

BoardGame::BoardGame()
{
    /* initialize to default values */
    celllength = 24;
    puzzleLocation.x = 200;
    puzzleLocation.y = 200;

    zoom = 1;
}
BoardGame::~BoardGame() {}

bool BoardGame::IsInBounds(PicPoint &p) {
    return IsInBounds(p.x, p.y);
}
bool BoardGame::IsInBounds(unsigned int x, unsigned int y) {
    return (x < width && y < height);
}

PicPoint BoardGame::GetLocation() {
    return PicPoint(&location);
}
bool BoardGame::TrySetLocation(PicPoint &p) {
    if (!IsInBounds(p))
        return false;

    location = p;

    return true;
}
bool BoardGame::TrySetLocationRel(int dx, int dy) {
    PicPoint p(location.x + dx, location.y + dy);

    if (!IsInBounds(location.x + dx, location.y + dy))
        return false;

    location.x += dx;
    location.y += dy;

    return true;
}

unsigned int BoardGame::GetElapsedTime() {
    return timer.GetTime();
}
