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

#include "b_tetris.h"

namespace BoardGame {

Tetris::Tetris(BoardSettings &s)
{
    width = s.x;
    height = s.y + stagingAreaHeight;

    /* initialize field */
    boardState.reset(new unsigned int[width * height]);
    for (unsigned int i = 0; i < width * height; i++)
        boardState[i] = BOARD_NONE;
}

bool Tetris::GameWon() {

    /* can't win at tetris */

    return false;
}
bool Tetris::GameLost() {
    /* TODO! */
    return false;
}

int Tetris::GetStateAt(Point &p) const {
    return GetStateAt(p.x, p.y);
}
int Tetris::GetStateAt(unsigned int x, unsigned int y) const {
    if (!IsInBounds(x, y))
        throw Exception("GetStateAt failed: Point not within board dimensions.");

    return boardState[CToI(x, y)];
}

int Tetris::GetMapAt(Point &p) const {
    return GetMapAt(p.x, p.y);
}
int Tetris::GetMapAt(unsigned int x, unsigned int y) const {

    /* we don't need / use the map in tetris */

    return GetStateAt(x, y);
}

void Tetris::DoOpAt(Point& /* unused parameter p*/, int op) {

    /* operations location is always determined by position of active piece */

    DoOp(op);
}
void Tetris::DoOp(int op) {
    /* TODO */
}

void Tetris::SetStateAt(Point& /* unused parameter p */, int /* unused parameter state */) {
    throw Exception("Setting states is handled internally in tetris.");
}

shared_ptr<StatsElement> Tetris::GetStats() const {
    /* TODO */

    throw Exception("Not implemented yet.");
}
}
