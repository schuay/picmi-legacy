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

#include "b_tetrispiece.h"

namespace BoardGame {

TetrisPiece::TetrisPiece(int x, int y)
{
    _currentX = x - ArraySize / 2;
    _currentY = y;

    _shape = rand() % T_BOARD_NONE;

    /* init state array */

    switch (_shape) {
    case T_BOARD_I:
        _state = { { 0, 1, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 0, 0} };
        break;
    case T_BOARD_J:
        _state = { { 0, 0, 0, 0},
                   { 0, 0, 1, 0},
                   { 0, 0, 1, 0},
                   { 0, 1, 1, 0} };
        break;
    case T_BOARD_L:
        _state = { { 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 1, 0} };
        break;
    case T_BOARD_O:
        _state = { { 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 1, 1, 0},
                   { 0, 1, 1, 0} };
        break;
    case T_BOARD_S:
        _state = { { 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 1, 0},
                   { 0, 0, 1, 0} };
        break;
    case T_BOARD_T:
        _state = { { 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 0, 1, 0},
                   { 0, 1, 1, 1} };
        break;
    case T_BOARD_Z:
        _state = { { 0, 0, 0, 0},
                   { 0, 0, 1, 0},
                   { 0, 1, 1, 0},
                   { 0, 1, 0, 0} };
        break;
    default:
        throw Exception("Invalid shape selected.");
    }


    /* determine random rotation */

    int rotation = rand() % 4;

    for (int i = 0; i < rotation; i++)
        RotateClockwise();
}

bool TetrisPiece::IsCovering(int x, int y) const {

    /* convert board to piece coordinates */

    x -= _currentX;
    y -= _currentY;

    /* and check if the piece is covering specified coord */
    return IsCoveringInPieceCoords(x, y);
}
bool TetrisPiece::IsCoveringInPieceCoords(int x, int y) const {
    if ((unsigned int)x >= ArraySize || (unsigned int)y >= ArraySize)
        return false;

    return _state[x][y];
}

void TetrisPiece::Move(MovementDirectionEnum dir) {

    switch (dir) {
    case MD_DOWN:
        _currentY++;
        break;
    case MD_UP:
        _currentY--;
        break;
    case MD_LEFT:
        _currentX--;
        break;
    case MD_RIGHT:
        _currentX++;
        break;
    default:
        break;
    }

}

void TetrisPiece::Rotate(RotationDirectionEnum rot) {
    if (rot == RD_CLOCKWISE)
        RotateClockwise();
    else
        RotateCounterclockwise();
}
void TetrisPiece::RotateClockwise() {

    int rotatedState[ArraySize][ArraySize];

    for (unsigned int i = 0; i < ArraySize; i++)
        for (unsigned int j = 0; j < ArraySize; j++)
            rotatedState[i][j] = _state[ArraySize - j - 1][i];

    for (unsigned int i = 0; i < ArraySize; i++)
        for (unsigned int j = 0; j < ArraySize; j++)
            _state[i][j] = rotatedState[i][j];
}
void TetrisPiece::RotateCounterclockwise() {

    for (int i = 0; i < 3; i++)
        RotateClockwise();

}

}
