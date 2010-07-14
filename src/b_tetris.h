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

#ifndef B_TETRIS_H
#define B_TETRIS_H

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <queue>

#include "b_boardgame.h"
#include "b_boardsettings.h"
#include "b_tetrispiece.h"
#include "b_tetrisdefines.h"
#include "b_tetrisstatselement.h"

using boost::shared_ptr;
using boost::shared_array;
using std::queue;

namespace BoardGame {

class Tetris : public BoardGame
{
public:
    Tetris(BoardSettings &s);


    /* virtual members of BoardGame */

    bool GameWon();
    bool GameLost();

    int GetStateAt(Point &p) const;
    int GetStateAt(unsigned int x, unsigned int y) const;

    int GetMapAt(Point &p) const;
    int GetMapAt(unsigned int x, unsigned int y) const;

    void DoOpAt(Point &p, int op);

    void DoOp(int op);

    shared_ptr<StatsElement> GetStats() const;

    void SetStateAt(Point &p, int state);

private:
    shared_array<unsigned int>
            boardState;

    queue<shared_ptr<TetrisPiece> >
            nextPieces;

    shared_ptr<TetrisPiece>
            currentPiece;

    static const unsigned int
            stagingAreaHeight = 4;
};

}
#endif // B_TETRIS_H
