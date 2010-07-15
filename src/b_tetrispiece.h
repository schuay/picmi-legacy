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

#ifndef B_TETRISPIECE_H
#define B_TETRISPIECE_H

#include <cstdlib>

#include "b_enums.h"
#include "b_exception.h"
#include "b_tetrisdefines.h"

namespace BoardGame {

class TetrisPiece
{
public:
    TetrisPiece(int x, int y);

    int GetShape() const { return _shape; }
    int GetCurrentX() const { return _currentX; }
    int GetCurrentY() const { return _currentY; }

    /* x and y are in BOARD coordinates. if the piece covers the specified coord,
       return true, else false */
    bool IsCovering(int x, int y) const;

    void Rotate(RotationDirectionEnum rot);

    void Move(MovementDirectionEnum dir);

    static const unsigned int ArraySize = 4;

private:

    /* location of left upper corner in board coordinates */
    int
            _currentX,
            _currentY;

    int _shape;
    bool _state[ArraySize][ArraySize];

    void RotateClockwise();
    void RotateCounterclockwise();
};

}

#endif // B_TETRISPIECE_H
