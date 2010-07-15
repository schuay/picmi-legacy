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

Tetris::Tetris(BoardSettings &s) : BoardGame()
{
    width = s.x;
    height = s.y + stagingAreaHeight;

    puzzleLocation.x = 20;
    puzzleLocation.y = 20;

    /* initialize field */

    boardState.reset(new unsigned int[width * height]);
    for (unsigned int i = 0; i < width * height; i++)
        boardState[i] = T_BOARD_NONE;

    currentPiece.reset(new TetrisPiece(width / 2, 0));
}

void Tetris::HandleLogic() {

    /* if ticks since last action are above a certain threshhold (depending on level),
       the current piece is moved down a step.
       if moving down is impossible (collision detection), move the pieces components to boardState,
       check for losing condition (piece not entirely in visible field)
       and spawn a new current piece. if this occurs, no further actions are possible in this turn,
       so mark it somehow

       as levelups are also time dependent, we also need to handle them here
     */

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

    if (currentPiece->IsCovering(x, y))
        return currentPiece->GetShape();
    else
        return boardState[CToI(x, y)];
}

void Tetris::DoOp(int op) {

    if (paused)
        return;

    if (op == T_OP_NONE)
        return;

    switch (op) {
    case T_OP_ROTATELEFT:
        currentPiece->RotateCounterclockwise();
        break;
    case T_OP_ROTATERIGHT:
        currentPiece->RotateClockwise();
        break;
    case T_OP_MOVELEFT:
        currentPiece->Move(MD_LEFT);
        break;
    case T_OP_MOVERIGHT:
        currentPiece->Move(MD_RIGHT);
        break;
    case T_OP_STEPDOWN:
        currentPiece->Move(MD_DOWN);
        break;
    case T_OP_DROPDOWN:
        /* TODO */
        break;
    default:
        break;
    }
}

shared_ptr<StatsElement> Tetris::GetStats() const {
    /* TODO */

    return shared_ptr<StatsElement>(new TetrisStatsElement());
}

/* unused / disabled functions */

void Tetris::DoOpAt(Point& /* unused parameter p*/, int /* unused parameter op */) {

    throw Exception("Operations location is always determined by position of active piece.");

}
void Tetris::SetStateAt(Point& /* unused parameter p */, int /* unused parameter state */) {

    throw Exception("Setting states is handled internally.");

}
int Tetris::GetMapAt(Point &p) const {
    return GetMapAt(p.x, p.y);
}
int Tetris::GetMapAt(unsigned int /* unused parameter x */, unsigned int /* unused parameter y */) const {

    throw Exception("Map is unneeded in tetris.");

}
}
