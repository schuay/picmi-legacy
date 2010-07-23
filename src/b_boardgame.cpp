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

#include "b_boardgame.h"
namespace BoardGame {
BoardGame::BoardGame()
{
    /* initialize to default values */
    celllength = 24;
    puzzleLocation.x = 200;
    puzzleLocation.y = 200;

    resolution = GR_INPROGRESS;

    quit = false;
    paused = false;
}
BoardGame::~BoardGame() {}

bool BoardGame::IsInBounds(Point &p) const {
    return IsInBounds(p.x, p.y);
}
bool BoardGame::IsInBounds(unsigned int x, unsigned int y) const {
    return (x < width && y < height);
}

Point BoardGame::GetLocation() const {
    return Point(&location);
}
bool BoardGame::TrySetLocation(Point &p) {
    if (paused)
        return false;

    if (!IsInBounds(p))
        return false;

    location = p;

    return true;
}
bool BoardGame::TrySetLocationRel(int dx, int dy) {
    if (paused)
        return false;

    Point p(location.x + dx, location.y + dy);

    if (!IsInBounds(location.x + dx, location.y + dy))
        return false;

    location.x += dx;
    location.y += dy;

    return true;
}

unsigned int BoardGame::GetElapsedTime() const {
    return timer.GetTime();
}
}
