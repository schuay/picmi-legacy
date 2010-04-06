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
#include <boost/shared_array.hpp>

#include "b_sweepdefines.h"
#include "b_boardsettings.h"
#include "b_boardgame.h"
#include "b_sweepstatselement.h"

namespace BoardGame {
class Sweeper : public BoardGame
{
public:
    Sweeper(BoardSettings &s);
    ~Sweeper();

    bool GameWon();
    bool GameLost();

    int GetStateAt(Point &p) const;
    int GetStateAt(unsigned int x, unsigned int y) const;

    int GetMapAt(Point &p) const;
    int GetMapAt(unsigned int x, unsigned int y) const;

    void SetStateAt(Point &p, int state);

    void DoOpAt(Point &p, int op);
    void DoOp(int op);

    unsigned int MarkedBombCount() const;
    unsigned int TotalBombCount() const { return bombCount; }

    boost::shared_ptr<StatsElement> GetStats() const;

private:

    void RandomPuzzle(BoardSettings &s);
    int CalcBombCount(Point &p) const;

    /* creates an array of all target points in targetArray and returns nr of neighbors */
    /* the caller is responsible for freeing the array */
    /* if noDiagonals is true, diagonal neighbors are not returned */
    boost::shared_array<Point> GetNeighborCoords(Point &p, int &targetCount, bool noDiagonals) const;

    /* exposing tiles is a recursive operation. expose all clear tiles connected to original tile. diagonal connections are not allowed */
    void ExposeTile(Point &p);

    /* this is called when clicking on an exposed tile. if the amount of marks matches the mapCount, start exposing all neighbors */
    void ExposeNeighborTiles();

    /* this is called once for the first operation in a game. automatically finds an empty area and exposes it */
    void ExposeInitialArea();

    /* solves the entire board - this is called once the game is won */
    void SolveBoard();

    static const int
            mapNone = 0,
            mapBomb = 9,
            boardClean = 0,
            boardExposed = 1,
            boardMarked = 2,
            boardTentative = 3;

    bool gameStarted;

    unsigned int bombCount;

    int *map,
        *boardState;
};
}
#endif // B_SWEEPER_H
