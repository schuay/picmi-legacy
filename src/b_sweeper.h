/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPER_H
#define B_SWEEPER_H

#include <cstdlib>
#include <cstdio>

#include "b_sweepdefines.h"
#include "b_boardsettings.h"
#include "b_boardgame.h"
namespace BoardGame {
class Sweeper : public BoardGame
{
public:
    Sweeper(BoardSettings &s);
    ~Sweeper();

    bool GameWon();

    int GetStateAt(Point &p);
    int GetStateAt(unsigned int x, unsigned int y);

    int GetMapAt(Point &p);
    int GetMapAt(unsigned int x, unsigned int y);

    void SetStateAt(Point &p, int state);

    void DoOpAt(Point &p, int op);
    void DoOp(int op);

private:

    void RandomPuzzle(BoardSettings &s);
    int CalcBombCount(Point &p);

    /* creates an array of all target points in targetArray and returns nr of neighbors */
    /* the caller is responsible for freeing the array */
    /* if noDiagonals is true, diagonal neighbors are not returned */
    Point *GetNeighborCoords(Point &p, int &targetCount, bool noDiagonals);

    /* exposing tiles is a recursive operation. expose all clear tiles connected to original tile. diagonal connections are not allowed */
    void ExposeTile(Point &p);

    static const int
            mapNone = 0,
            mapBomb = 9,
            boardClean = 0,
            boardExposed = 1,
            boardMarked = 2,
            boardTentative = 3;

    int *map,
        *boardState;
};
}
#endif // B_SWEEPER_H
