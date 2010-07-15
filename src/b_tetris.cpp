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

    tickForNextAction = 0;
    SkipLogic = false;

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

    if (SkipLogic)
        SkipLogic = false;

    const unsigned int
            ticksBetweenActions = 500,
            currentTicks = SDL_GetTicks();

    /* initialize tickForNextAction */
    if (tickForNextAction == 0)
        tickForNextAction = currentTicks - 1;

    if (currentTicks > tickForNextAction) {
        TryMove(MD_DOWN);
        tickForNextAction += ticksBetweenActions;
    }
}

bool Tetris::IsCollision() const {
    /* collisions occur both if a coordinate is filled and if a piece is out of bounds */

    int
            x = currentPiece->GetCurrentX(),
            y = currentPiece->GetCurrentY(),
            curX, curY;

    for (unsigned int dx = 0; dx < TetrisPiece::ArraySize; dx++) {
        for (unsigned int dy = 0; dy < TetrisPiece::ArraySize; dy++) {

            curX = x + dx;
            curY = y + dy;

            if (currentPiece->IsCovering(curX, curY)) {

                if (!IsInBounds(curX, curY))
                    return true;
                else if (boardState[curY * width + curX] != T_BOARD_NONE)
                    return true;
            }
        }
    }

    return false;
}

void Tetris::TryRotate(RotationDirectionEnum rot) {

    currentPiece->Rotate(rot);

    if (IsCollision()) {

        RotationDirectionEnum oppositeRot =
                rot == RD_CLOCKWISE ?
                RD_COUNTERCLOCKWISE :
                RD_CLOCKWISE;

        currentPiece->Rotate(oppositeRot);
    }
}
void Tetris::TryMove(MovementDirectionEnum dir) {

    /* simple collision detection consists of actually moving a piece and checking if
       any coords overlap with boardState. if they do, move the piece back */

    currentPiece->Move(dir);

    if (IsCollision()) {
        MovementDirectionEnum oppositeDir =
                (MovementDirectionEnum)((dir + 2) % 4);

        currentPiece->Move(oppositeDir);

        if (dir == MD_DOWN)
            PieceToBoardState();
    }
}
void Tetris::PieceToBoardState() {

    int
            x = currentPiece->GetCurrentX(),
            y = currentPiece->GetCurrentY(),
            curX, curY;

    for (unsigned int dx = 0; dx < TetrisPiece::ArraySize; dx++) {
        for (unsigned int dy = 0; dy < TetrisPiece::ArraySize; dy++) {

            curX = x + dx;
            curY = y + dy;

            if (currentPiece->IsCovering(curX, curY))
                boardState[curY * width + curX] = currentPiece->GetShape();
        }
    }

    currentPiece.reset(new TetrisPiece(width / 2, 0));

    SkipLogic = true;
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
        TryRotate(RD_COUNTERCLOCKWISE);
        break;
    case T_OP_ROTATERIGHT:
        TryRotate(RD_CLOCKWISE);
        break;
    case T_OP_MOVELEFT:
        TryMove(MD_LEFT);
        break;
    case T_OP_MOVERIGHT:
        TryMove(MD_RIGHT);
        break;
    case T_OP_STEPDOWN:
        TryMove(MD_DOWN);
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
