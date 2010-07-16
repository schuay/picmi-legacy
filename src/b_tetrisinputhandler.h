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

#ifndef B_TETRISINPUTHANDLER_H
#define B_TETRISINPUTHANDLER_H

#include <SDL/SDL.h>

#include "b_inputhandler.h"
#include "b_tetris.h"

namespace BoardGame {

class TetrisInputHandler : public InputHandler
{
public:
    TetrisInputHandler(BoardGame *p);

    void HandleInput();

private:

    Tetris *game;

    Timer timer;
    unsigned int timeOfLastAction;
};

}

#endif // B_TETRISINPUTHANDLER_H
